-module(nueve).
-export([start/1]).

nodo(ParentPid) ->
    receive
        {msg, N} ->
            if N > 0 ->
                io:format("Process ~w, recibe ~w y enviará ~w~n", [self(), N, N - 1]),
                timer:sleep(1000),
                ParentPid ! {msg, N - 1},
                nodo(ParentPid);
            true ->
                io:format("Process ~w, recibe 0, morirá ~n", [self()]),
                ParentPid ! {exit},
                ok
            end;
        {exit} ->
            io:format("Process ~w, recibe exit~n", [self()]),
            ParentPid ! {exit},
            ok
    end.

start(0, ParentPid, M) -> 
    Pid = spawn(fun () -> nodo(ParentPid) end),
    Pid ! {msg, M + 2},
    nodo(Pid);
start(N, ParentPid, M) ->
    Pid = spawn(fun () -> nodo(ParentPid) end),
    start(N - 1, Pid, M + 1).
    
start(N) ->
    start(N - 1, self(), 0).


