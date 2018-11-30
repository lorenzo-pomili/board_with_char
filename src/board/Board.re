let default_edge = 8;

type coord = {
  x: int,
  y: int,
};

type character = {
  name: string,
  coord,
};

type cell = {
  coord,
  character: option(character),
};

type row = list(cell);

type board = list(row);

type direction =
  | Up
  | Down
  | Left
  | Right;

let (<=>) = (c1, c2) => c1.x == c2.x && c1.y == c2.y;

let getNewCharacter = (name, coord) => {name, coord};

let getNewCood = (coord, direction) =>
  switch (direction) {
  | Up =>
    if (coord.y == 0) {
      coord;
    } else {
      {...coord, y: coord.y - 1};
    }
  | Down =>
    if (coord.y == default_edge) {
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
    if (coord.x == default_edge) {
      coord;
    } else {
      {...coord, x: coord.x + 1};
    }
  };

let getC = (x, y) => {
  coord: {
    x,
    y,
  },
  character: None,
};

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
};

let getBoardWithCharacter = (board: board, character: character) =>
  Belt.List.map(board, row =>
    Belt.List.map(row, c =>
      if (c.coord <=> character.coord) {
        {...c, character: Some(character)};
      } else {
        c;
      }
    )
  );
