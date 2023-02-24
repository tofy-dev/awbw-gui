/*
  * Basic javascript parser for https://awbw.amarriner.com/terrain_map.php
  * Constructs an string array from the Terrain ID/Name inputs
    * e.g. container[4] => HRiver
  * This is run in the javascript console, and the results are copied for board construction
*/

let container = [];
let tbody = document.querySelector("tbody")
for (let row = 1; row < tbody.childElementCount; row++) {
  let id = tbody.children[row].children[1].textContent;
  let name = tbody.children[row].children[3].textContent;

  while (container.length < id) container.push("");
  container.push(name);
}

console.log(JSON.stringify(container))
