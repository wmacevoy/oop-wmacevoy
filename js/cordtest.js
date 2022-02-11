import { Cord, Equipment } from './cord.mjs'

const yellow = new Cord(25,"female 240 twist lock",40);


console.assert(yellow.capacity === 41);
console.assert(yellow.connector === "female 240 twist lock");
console.assert(yellow.length === 25);
console.assert(yellow.opposite === "male 240 twist lock");

const black = new Cord(25,"female 120 3-prong",20);

const waterThingy = new Equipment(5,"male 120 3-prong",false);

console.log(`black cord is compatible with water thing: ${black.compatible(waterThingy)}`);

