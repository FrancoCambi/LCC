-module(hello).
-export([init/0]).

hello() ->
	receive after 1000 -> ok end,
	io:fwrite("Hello ~p~n", [case rand:uniform(10) of 10 -> 1/uno; _ -> self() end]),
	hello().

safe_hellp() ->
    catch hello().

catcher(Pid) ->
    receive
        {'EXIT', Pid, _Reason} ->
            io:format("~p crashed! Lets try again.~n", [Pid]),
            NewPid = spawn_link(fun () -> safe_hello() end),
            catcher(NewPid)
    end.

init() ->
    process_flag(trap_exit, true),
    HelloPid = spawn_link(fun () -> safe_hello() end),
    catcher(HelloPid).