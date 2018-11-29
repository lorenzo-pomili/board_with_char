let default_edge = 8;

type coord = {
  x: int,
  y: int,
};

type row = list(coord);

type board = list(row);

type direction =
  | Up
  | Down
  | Left
  | Right;

let getNewCood = (coord, direction) =>
  switch (direction) {
  | Up =>
    if (coord.y == 0) {
      coord;
    } else {
      {...coord, y: coord.y - 1};
    }
  | Down =>
    if (coord.y == default_edge - 1) {
      coord;
    } else {
      {...coord, y: coord.y + 1};
    }
  | Left =>
    if (coord.x == 0) {
      coord;
    } else {
      {...coord, x: coord.x - 1};
    }
  | Right =>
    if (coord.x == default_edge - 1) {
      coord;
    } else {
      {...coord, x: coord.x + 1};
    }
  };

/* let getC = (x, y) => {x, y};

   let makeRow = (edge, n) => {
     let rec aux = (e, acc) =>
       if (e < 0) {
         acc;
       } else {
         aux(e - 1, [getC(e, n), ...acc]);
       };
     aux(edge, []);
   };

   let makeBoard = edge => {
     let rec aux = (e, acc) =>
       if (e < 0) {
         acc;
       } else {
         aux(e - 1, [makeRow(edge, e), ...acc]);
       };
     aux(edge, []);
   }; */

/* TODO: should be a grid */
let makeCells = n => {
  let rec aux = (acc, x) =>
    if (x < 0) {
      acc;
    } else {
      aux([x, ...acc], x - 1);
    };
  aux([], n - 1);
};
