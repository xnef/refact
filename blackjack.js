const random = require("./random");
const mast = ["Пик","Треф","Червей","Бубен"]
const coloda = [
    {name:"Туз",num:1},
    {name:"Двойка",num:2},
    {name:"Тройка",num:3},
    {name:"Четверка",num:4},
    {name:"Пятерка",num:5},
    {name:"Шестерка",num:6},
    {name:"Семерка",num:7},
    {name:"Восьмерка",num:8},
    {name:"Девятка",num:9},
    {name:"Десятка",num:10},
    {name:"Валет",num:10},
    {name:"Дама",num:10},
    {name:"Король",num:10}
]

class Score{

    constructor(name){
        this.name = name;
        this.cards = [];
        this.ace_count = 0;
        this.score = 0;  
    }
    add_card(){
        let card =coloda[random.randomNArr(coloda.length)];
        if(card.name==="Туз")this.ace_count+=1;
        card = {
            name: card.name+" "+mast[random.randomNArr(mast.length)],
            num: card.num,
        }
        this.cards.push(card);
        this.score += card.num;
    }
}

function score_check(pl){
    let temp=pl.score;
    for(let i=0;i<=pl.ace_count&&temp<22;i++)temp+=10;
    temp-=10;
    return temp; 
}

function card_print(pl){
    console.log(pl.name+", карты:");
    pl.cards.forEach(element => {
        console.log(element.name);
    });
    let str="Очки: "
    
    str+=score_check(pl); 
    
    
    console.log (str);
}

let player,dealer
let stage = [false];
function game(){
    if(!stage[0]) {
    console.log("Бесконечная колода\n")
    player= new Score("Игрок");
    dealer=new Score("Дилер");
    dealer.add_card();
    player.add_card(); player.add_card();
    card_print(player);
    stage[0]=true;
    }
    function playing(){
        score = score_check(player);
        
    }
}


game();



