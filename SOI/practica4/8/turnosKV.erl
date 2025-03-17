% Este codigo no soporta paquetes fragmentados pero maneja un Mapa de pares 
% Key Value y sus operaciones correctamente. (memcached)

-module(turnosKV).
-export([server/0]).

-define(PORT, 8003).

server() ->
    register(pidMap, spawn (fun () -> map_handler (maps:new()) end)), % Creo el Map
	{ok, ListenSocket} = gen_tcp:listen(?PORT, [{reuseaddr, true}]), % listen
	io:format("El servidor de turnos se pone en escucha, puerto: ~p~n", [?PORT]),
    wait_for_clients(ListenSocket, 0).

map_handler(Map) ->
    receive
        {Pid, {put, Key, Value}} -> 
            NewMap = maps:put(Key, Value, Map),
            Pid ! {ok},
            map_handler(NewMap);
        {Pid, {del, Key}} -> 
            NewMap = maps:remove(Key, Map),
            Pid ! {ok},
            map_handler(NewMap);
        {Pid, {get, Key}} -> 
            Value = maps:get(Key, Map, error),
            case Value of
                error -> Pid ! {error, "NOTFOUND"};
                _ -> Pid ! {ok, Value}
            end,
            map_handler(Map)
    end.

wait_for_clients(ListenSocket, N) ->
	{ok, Socket} = gen_tcp:accept(ListenSocket), % bloqueante
	spawn (fun () -> wait_for_clients (ListenSocket, N + 1) end),
	io:format("Se conectó correctamente (process ~p) con el cliente: ~p~n", [N, Socket]),
    wait_for_command(Socket).

wait_for_command(Socket) ->
	receive
        {tcp, Socket, CommandLine} ->
            Output = process_command(CommandLine),
            Reply = process_output(Output),
            gen_tcp:send(Socket, Reply),
            wait_for_command(Socket);
        {tcp_closed, Socket} ->
            io:format("Se ha desconectado el cliente: ~p~n", [Socket]),
            gen_tcp:close(Socket);
        _ ->
            wait_for_command(Socket)
    end.

remove_newline(CommandLine) ->
  string:trim(CommandLine, trailing, "\n").

process_command(CommandLine) ->
    case string:tokens(remove_newline(CommandLine), " ") of
        [Command, Key, Value] ->
            case {Command, Key, Value} of
                {"PUT", Key, Value} ->
                    pidMap ! {self(), {put, Key, Value}},
                    receive
                        {ok} -> {ok}
                    end;
                _ ->
                    {error, "EINVAL"}
            end;
        [Command, Key] ->
            case {Command, Key} of
                {"DEL", Key} ->
                    pidMap ! {self(), {del, Key}},
                    receive
                        {ok} -> {ok}
                    end;
                {"GET", Key} ->
                    pidMap ! {self(), {get, Key}},
                    receive
                        {ok, Value} -> {ok, Value};
                        {error, Msg} -> {error, Msg}
                    end;
                _ ->
                    {error, "EINVAL"}
            end;
        _ ->
            {error, "EINVAL"}
    end.

process_output(Result) ->
    case Result of
        {ok} ->
            "OK\n";
        {ok, Value} ->
            "OK " ++ Value ++ "\n";
        {error, Reason} ->
            Reason ++ "\n"
    end.