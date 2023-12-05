reset = Module.cwrap("reset", "number", []);
player_move = Module.cwrap("player_move", "number", ["number"]);
ai_move = Module.cwrap("ai_move", "number", []);
get_key = Module.cwrap("get_key", "string", []);
has_finished = Module.cwrap("has_finished", "int", []);

mutex = false;

async function click_handler(i){
    if(!mutex)
        return;

    move = player_move(i);
    console.log(move);
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
        await type_and_untype("Wait, we DREW!?");
        await type_and_untype("...no, it must be a bug");
        await clear_game();
        await next_move();
    }

    if (result == 1) {
        await type_and_untype("HA! I knew I would win!!");
        await clear_game();
        await next_move();
    }

    if (result == 2) {
        await type_and_untype("Wait WHAT!!!");
        await type_and_untype("YOU WON!");
        await type_and_untype("NO, that's not possible!!");
        await type_and_untype("Meh, whatever");
        await type_and_untype("I'm out of here");
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
        just_type("I don't even need to check this move!")
    }
    else{
        just_type("You never stood a chance!");
    }
    
    mutex = true;
}

async function alert_won(element){
    await type_text(element);
    alert("Congrats, owl! You beat the Winter Grinch! This means that school can officially be let out now! However, I heard that a few other owls are stuck in school still as the Winter Grinch told their teacher not to let them out! You must help them! https://scratch.mit.edu/projects/934669354");
}


var text_terminal;
window.onload = async function(){


    if (localStorage.getItem("key") !== null) {
        document.body.innerHTML = "<iup-terminal id=\"main_terminal\"></iup-terminal>";
        let element = document.getElementById("main_terminal").getElementsByClassName("terminal_text")[0];
        element.innerText = "Error: \"Executable not found at /usr/bin/TicTacToe.sh\"";
        alert_won(element);
        return;
    }

    text_terminal = document.getElementById("typing_terminal").getElementsByClassName("terminal_text")[0];
    await type_and_untype("Hello there human!");
    await type_and_untype("I have stolen your winter,");
    await type_and_untype("and you can't get it back!");
    await type_and_untype("That is, unless you beat me");
    await type_and_untype(".. at tic tac toe!");
    await type_and_untype("like that could ever happen");
    next_move();

}