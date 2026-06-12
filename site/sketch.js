// ----- Paramètres -----
let echelle = 1000000000; // 1 px = 1e9 m
let cx = 200; // centre du soleil sur le canvas (x)
let cy = 200; // centre du soleil sur le canvas (y)

// ----- État -----
let dataJSON = null;
let methods = [];   // toutes les trajectoires du fichier
let a = 0;          // index du point courant
let trajLoaded = false;
let infoDiv;


let colors = [
  [239,  68,  68],  
  [ 56, 189, 248],
  [ 52, 211, 153],
  [251, 146,  60],
  [244, 114, 182]
];

function setup() {
  let canvas = createCanvas(720, 400);
  canvas.parent(document.body);
  noLoop();
  infoDiv = document.getElementById("infos");

  let button = createButton("reset");
  button.mousePressed(reset);
}

function readFile(input) {
  let file = input.files[0];
  if (!file) return;
  let reader = new FileReader();
  reader.readAsText(file);
  reader.onload = function () {
    try {
      dataJSON = JSON.parse(reader.result);
      methods = Object.keys(dataJSON);
      a = 0;
      trajLoaded = true;
      redraw();
    } catch (e) {
      console.log("Erreur de lecture JSON :", e);
      infoDiv.innerHTML = "Erreur : fichier JSON invalide.";
    }
  };
  reader.onerror = function () {
    console.log(reader.error);
  };
}

function reset() {
  a = 0;
  redraw();
}

function drawOrbit(points, col) {
  stroke(col[0], col[1], col[2], 90);
  noFill();
  beginShape(POINTS);
  for (let i = 0; i < points.length; i++) {
    let x = cx + points[i][0][0] / echelle;
    let y = cy + points[i][0][1] / echelle;
    vertex(x, y);
  }
  endShape();
}

function minLength() {
  let len = Infinity;
  for (let m of methods) {
    len = min(len, dataJSON[m].length);
  }
  return len;
}

function draw() {
  background(7, 9, 22);

  randomSeed(99);
  noStroke();
  for (let i = 0; i < 120; i++) {
    let sx = random(width);
    let sy = random(height);
    let br = random(80, 200);
    fill(255, 255, 255, br);
    circle(sx, sy, random(0.6, 1.8));
  }

  noStroke();
  fill(255, 200, 60, 25);
  circle(cx, cy, 70);
  fill(255, 210, 80, 40);
  circle(cx, cy, 50);
  fill(255, 217, 102);
  circle(cx, cy, 30);
  fill(255, 245, 180);
  circle(cx, cy, 14);

  if (!trajLoaded) {
    fill(184, 180, 204);
    textAlign(CENTER, CENTER);
    text("Aucune trajectoire chargée", width / 2, height / 2);
    return;
  }

  for (let i = 0; i < methods.length; i++) {
    let col = colors[i % colors.length];
    drawOrbit(dataJSON[methods[i]], col);
  }

  let len = minLength();
  for (let i = 0; i < methods.length; i++) {
    let col = colors[i % colors.length];
    let pt = dataJSON[methods[i]][a];
    let x = cx + pt[0][0] / echelle;
    let y = cy + pt[0][1] / echelle;

    noStroke();
    fill(col[0], col[1], col[2], 50);
    circle(x, y, 22);
    fill(col[0], col[1], col[2]);
    stroke(255, 255, 255, 80);
    strokeWeight(0.8);
    circle(x, y, 10);
  }

  textAlign(LEFT, TOP);
  noStroke();
  for (let i = 0; i < methods.length; i++) {
    let col = colors[i % colors.length];
    fill(col[0], col[1], col[2]);
    circle(15, 15 + i * 18, 8);
    fill(232, 230, 240);
    text(methods[i], 28, 10 + i * 18);
  }

  let t = dataJSON[methods[0]][a][2];
  infoDiv.innerHTML = "Point n°" + a + " / " + (len - 1) + " — temps = " + t;

  if (a < len - 1) {
    a = a + 1;
  } else {
    a = 0;
  }
}

function mousePressed() {
  if (mouseButton === LEFT && trajLoaded
      && mouseX >= 0 && mouseX <= width
      && mouseY >= 0 && mouseY <= height) {
    loop();
  }
}

function mouseReleased() {
  noLoop();
}
