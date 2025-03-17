-module(trece).
-export([start/1, step/3]).

send(Pid, Value) ->
    if
        Pid == noPid ->
            Value;
        true ->
            Pid ! {self(), Value}
    end.

step(I, N, Pid) ->
    if
        N - I == 1 ->
            send(Pid, I);
        true ->
            M = (I + N) div 2,
            PidRight = spawn_link(?MODULE, step, [M, N, self()]),
            ValueLeft = step(I, M, noPid),
            receive
                {PidRight, ValueRight} ->
                    send(Pid, ValueLeft + ValueRight)
            end
    end.

start(N) ->
    process_flag(trap_exit, true),
    Value = step(0, N, noPid),
    receive
        {'EXIT', _, normal} ->
            io:fwrite("Resultado: ~p~nResultado esperado: ~p~n", [Value, (N * (N - 1) div 2)]);
        {'EXIT', _, Reason} ->
            io:fwrite("El calculo fallo debido a un error, ~p~n", [Reason])
    end.