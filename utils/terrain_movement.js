/*
  * Basic javascript parser for https://awbw.amarriner.com/terrain.php
*/

{

let tbody = document.querySelectorAll("tbody")[1];

let clear = [];
let rain = [];
let snow = [];

let cols = 8;

for (let row = 2; row < tbody.childElementCount; row++) {
  clear.push([]);
  for (let col = 2; col < 2+cols; col++) {
    clear[clear.length-1].push(tbody.children[row].children[col].children[0].textContent.trim())
  }
}
for (let row = 2; row < tbody.childElementCount; row++) {
  rain.push([]);
  for (let col = 2+cols; col < 2+cols*2; col++) {
    rain[rain.length-1].push(tbody.children[row].children[col].children[0].textContent.trim())
  }
}
for (let row = 2; row < tbody.childElementCount; row++) {
  snow.push([]);
  for (let col = 2+cols*2; col < 2+cols*3; col++) {
    snow[snow.length-1].push(tbody.children[row].children[col].children[0].textContent.trim())
  }
}

console.log(JSON.stringify(clear))
console.log(JSON.stringify(rain))
console.log(JSON.stringify(snow))
}
