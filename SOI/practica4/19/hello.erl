-module(hello).
-export([init/0, change_message/1]).

hello(Msg) ->
	receive 
        {update, NewMsg} -> hello(NewMsg)
    after 1000 -> 
        ok, 
	    io:fwrite("~s ~p~n", [Msg, case rand:uniform(10) of 10 -> 1/uno; _ -> self() end]),
	    hello(Msg)
    end.

safe_hello(Msg) ->
    catch hello(Msg).

catcher(Pid) ->
    receive
        {'EXIT', Pid, _Reason} ->
            io:format("~p crashed! Lets try again.~n", [Pid]),
            NewPid = spawn_link(fun () -> safe_hello("Hello") end),
            catcher(NewPid);
        {update, NewMsg} ->
            Pid ! {update, NewMsg},
            catcher(Pid)
    end.

change_message(NewMsg) -> catcherPid ! {update, NewMsg}.

msg_changer(Msg) ->
    receive after 10000 -> change_message(Msg) end.

init() ->
    process_flag(trap_exit, true),
    HelloPid = spawn_link(fun () -> safe_hello("Hello") end),
    spawn(fun () -> msg_changer("Hola") end),
    register(catcherPid, self()),
    catcher(HelloPid).
