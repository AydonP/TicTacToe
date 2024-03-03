
const Status = {
    empty: 0,
    player: 1,
    com: 2
}

class Box extends HTMLElement {
    static observedAttributes = ["style", "status"];
    template = document.getElementById("_Box").content;
    style = "";
    status = Status.empty;

    constructor() {
        super();
    }

    apply_status(){
        let element = this.firstElementChild;
        if(element != null){
            switch (Number(this.status)) {
                case Status.empty:
                    element.classList.remove("snowman");
                    element.classList.remove("snowflake");
                    break;
                case Status.player:
                    element.classList.remove("snowflake");
                    element.classList.add("snowman");
                    break;
                case Status.com:
                    element.classList.remove("snowman");
                    element.classList.add("snowflake");
                    
                    break;
                default:
                    break;
            }
        }
    }

    apply_style(){
        if(this.firstChild !== null)
            this.firstChild.style = this.style;
    }

    connectedCallback() {
        this.appendChild(this.template.cloneNode(true));
        this.apply_style();
        this.apply_status();
    }

    attributeChangedCallback(name, _, value) {
        switch (name) {
            case "style":
                this.style = value;
                this.apply_style();
                break;
            case "status":
                this.status = value;
                this.apply_status();
                break;
        }
    }
}

customElements.define("game-box", Box);


class Board extends HTMLElement {
    static observedAttributes = ["style", "status"];

    style = "";
    size = 9;
    columns = 3;
    rows = 3;

    template(div, count = 9){
        for (let i = 0; i < count; i++) {
            let child = document.createElement("game-box");
            child.onclick = function(){
                click_handler(i);
            };
            child.classList.add( "button" + i)
            div.appendChild(child);
        }
        return div;
    }

    constructor() {
        super();
    }

    clear(){
        this.childNodes.forEach(child => {
            child.status = Status.empty();
        });
    }

    apply_size(){
        
        if (size > this.childElementCount) {
            this.template(this.firstChild, size - this.childElementCount)
            this.clear()
        }
        else if (size < this.childElementCount) {
            for (let i = this.childElementCount - size; i > 0; i++) {
                this.removeChild(this.lastElementChild);
                this.clear();
            }
        }
    }

    apply_style(){
        if(this.firstChild !== null)
            this.firstChild.style = this.style;
    }

    apply_grid(){
        if(this.firstChild !== null){
            this.firstChild.style["grid-template-columns"] = "repeat(" + this.columns + ", 1fr)";
            this.firstChild.style["grid-template-rows"] = "repeat(" + this.rows + ", 1fr)";
        }
    }

    connectedCallback() {
        this.appendChild(this.template(document.createElement("div"), this.size));
        this.apply_style();
        this.apply_grid();
    }

    attributeChangedCallback(name, _, value) {
        switch (name) {
            case "style":
                this.style = value;
                this.apply_style();
                break;
            case "size":
                this.size = value;
                this.apply_size();
        }
    }
}


customElements.define("game-board", Board);


class Terminal extends HTMLElement {
    static observedAttributes = ["style", "status"];
    template = document.getElementById("_Terminal").content;
    style = "";

    constructor() {
        super();
    }

    apply_style(){
        if(this.firstChild !== null)
            this.firstChild.style = this.style;
    }

    connectedCallback() {
        this.appendChild(this.template.cloneNode(true));
        this.apply_style();
    }

    attributeChangedCallback(name, _, value) {
        switch (name) {
            case "style":
                this.style = value;
                this.apply_style();
                break;
        }
    }
}

customElements.define("game-terminal", Terminal);

class Window extends HTMLElement {
    static observedAttributes = ["style", "status"];
    template = document.getElementById("_Window").content;
    style = "";

    constructor() {
        super();
    }

    apply_style(){
        if(this.firstChild !== null)
            this.firstChild.style = this.style;
    }

    connectedCallback() {
        this.appendChild(this.template.cloneNode(true));
        this.apply_style();
    }

    attributeChangedCallback(name, _, value) {
        switch (name) {
            case "style":
                this.style = value;
                this.apply_style();
                break;
        }
    }
}

customElements.define("game-window", Window);

//Typing Text Functions
const delay = ms => new Promise(res => setTimeout(res, 2000));

async function _type_text(element, durration, reverse = false){
    let animation = element.animate(
        [
            { clipPath: "xywh(0 0 0 100%)"},
            { clipPath: `xywh(0 0 ${element.innerText.length}ch 100%)` },
        ],
        {
            duration: element.innerText.length * durration,
            iterations: 1,
            easing: "steps(" + element.innerText.length + ", end)",
            fill: "forwards",
     });
    
    if(reverse)
        animation.reverse();

    await animation.finished;
    animation.commitStyles();
    return element;
}

async function type_text(element, durration = 25){
    await _type_text(element, durration, false);
}

async function untype_text(element, durration = 25){
    await _type_text(element, durration, true);
}

