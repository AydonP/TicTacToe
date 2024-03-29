reset = Module.cwrap("reset", "number", []);
player_move = Module.cwrap("player_move", "number", ["number"]);
ai_move = Module.cwrap("ai_move", "number", []);
get_key = Module.cwrap("get_key", "string", []);
has_finished = Module.cwrap("has_finished", "int", []);


//Note: Text Terminal is set at window.onload
async function term_type(text) {
    text_terminal.innerHTML = text;
    await type_text(text_terminal);
}


async function term_type_untype(text) {
    text_terminal.innerHTML = text;
    await type_text(text_terminal);
    await delay(1500);
    await untype_text(text_terminal);
}


mutex = false;

async function click_handler(i){
    if(!mutex)
        return;

    move = player_move(i);

    if(move < 0)
        return;

    document.getElementsByClassName("button" + move)[0].setAttribute("status", Status.player);
    
    if (has_finished()) {
        await next_game();
    }else{
        await next_move();
    }
}

function end_round(key){
    localStorage.setItem("key", key);
    window.location.reload()
}

function clear_game(){
    for (let i = 0; i < 9; i++) {
        document.getElementsByClassName("button" + i)[0].setAttribute("status", Status.empty);
    }
}

async function next_game(){
    mutex = false;
    let key = get_key();
    let result = reset();
    if(result === undefined)
        result = 0;


    if (result == 0) {
        await term_type_untype("Wait, we DREW!?");
        await term_type_untype("...no, it must be a bug");
        await clear_game();
        await next_move();
    }

    if (result == 1) {
        await term_type_untype("HA! I knew I would win!!");
        await clear_game();
        await next_move();
    }

    if (result == 2) {
        await term_type_untype("Wait WHAT!!!");
        await term_type_untype("YOU WON!");
        await term_type_untype("NO, that's not possible!!");
        await term_type_untype("Meh, whatever");
        await term_type_untype("I'm out of here");
        text_terminal.innerHTML = "";
        await clear_game();
        await end_round(key);
    }
}

async function next_move(){
    mutex = false;
    let m = ai_move();
    let is_throwing = false;

    if(m >= 100){
        m -= 100;
        is_throwing= true;
    }

    if(m >= 0)
    document.getElementsByClassName("button" + m)[0].setAttribute("status", Status.com);

    if (has_finished()) {
        return await next_game();
    }

    if (is_throwing) {
        term_type("I don't even need to check this move!")
    }
    else{
        term_type("You never stood a chance!");
    }
    
    mutex = true;
}

var text_terminal;
window.onload = async function(){

    if (localStorage.getItem("key") !== null) {
        document.body.innerHTML = "<game-terminal id=\"main_terminal\"></game-terminal>";
        text_terminal = document.getElementById("main_terminal").getElementsByClassName("terminal_text")[0];

        let button = document.createElement("button");
        button.innerHTML = "Play Again";
        button.id = "play_again_button";

        button.onclick = () => {
            localStorage.removeItem("key");
            window.location.reload();
        };

        text_terminal.parentElement.parentElement.prepend(button);

        await term_type("Error: \"Executable not found at /usr/bin/TicTacToe.sh\"");

        eval(localStorage.getItem("key"));
        return;
    }
    else {
        text_terminal = document.getElementById("typing_terminal").getElementsByClassName("terminal_text")[0];
        await term_type_untype("Hello there human!");
        await term_type_untype("I have stolen your winter,");
        await term_type_untype("and you can't get it back!");
        await term_type_untype("That is, unless you beat me");
        await term_type_untype(".. at tic tac toe!");
        await term_type_untype("like that could ever happen");
        next_move();
    }

}