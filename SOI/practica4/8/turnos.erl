-module(turnos).
-export([server/0]).

-define(PORT, 8004).

server() ->
    register(pidCounter, spawn (fun () -> counter_handler (0) end)),
	{ok, ListenSocket} = gen_tcp:listen(?PORT, [{reuseaddr, true}]), % listen
	io:format("El servidor de turnos se pone en escucha, puerto: ~p~n", [?PORT]),
    wait_for_clients(ListenSocket, 0).

counter_handler(N) ->
	receive
		{new, Pid} -> 
			Pid ! {newN,N},
		counter_handler(N+1);
		_ -> counter_handler(N)
	end.

wait_for_clients(ListenSocket, N) ->
	{ok, Socket} = gen_tcp:accept(ListenSocket), % bloqueante
	spawn (fun () -> wait_for_clients (ListenSocket, N + 1) end),
	io:format("Se conectó correctamente (process ~p) con el cliente: ~p~n", [N, Socket]),
    wait_for_command(Socket, "").

wait_for_command(Socket, BufferMsg) ->
	receive
		% This is from client
		{tcp, Socket, CommandLine} -> 
			Leftovers = process_command(string:split(BufferMsg ++ CommandLine, "\n")),
			wait_for_command(Socket, Leftovers);
		{tcp_closed, Socket} ->
            io:format("Se ha desconectado el cliente: ~p~n", [Socket]),
            gen_tcp:close(Socket);
		{error, _} -> 
			gen_tcp:close(Socket);
		% This is from itself
		{newN, N} -> 
			gen_tcp:send(Socket, [integer_to_list(N) ++ "\n", 0]),
			wait_for_command(Socket, BufferMsg);
		{close} ->
			gen_tcp:close(Socket)
	end.

process_command([]) -> "";
process_command([H]) -> 
	case process_output(H) of 
		error -> H;
		_ -> ""
	end;
process_command([H|Ts]) -> 
	process_output(H),
	process_command(Ts).

process_output(Msg) ->
	case Msg of 
		"NUEVO" -> 
			pidCounter ! {new, self()},
			ok;
		"CHAU" -> 
			self() ! {close}, 
			ok;
		_ ->
			error
	end.