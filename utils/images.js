/*
  * Basic javascript parser for https://awbw.amarriner.com/terrain_map.php
  * Downloads all images, uses shell script as well
*/

let container = [];
let tbody = document.querySelector("tbody")
for (let row = 1; row < tbody.childElementCount; row++) {
  let img = tbody.children[row].children[0].children[0];
  container.push(img.src);
}

console.log(JSON.stringify(container))
