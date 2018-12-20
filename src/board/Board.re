let default_edge = 8;

type coord = {
  x: int,
  y: int,
};

type direction =
  | Up
  | Down
  | Left
  | Right;

type pathEl = {
  coord,
  direction,
};

type path = list(pathEl);

type character = {
  name: string,
  moving: option(direction),
  coord,
};

type boardElement =
  | Character(character)
  | Path(pathEl);

type cell = {
  coord,
  element: option(boardElement),
};

type row = list(cell);

type board = list(row);

let getElementCoord = e =>
  switch (e) {
  | Character(c) => c.coord
  | Path(p) => p.coord
  };

let (<=>) = (c1, c2) => c1.x == c2.x && c1.y == c2.y;

let getNewCharacter = (name, coord) => {name, coord, moving: None};

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
  element: None,
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

let getBoardWithElement = (board: board, element: boardElement) =>
  Belt.List.map(board, row =>
    Belt.List.map(row, c =>
      if (c.coord <=> getElementCoord(element)) {
        {...c, element: Some(element)};
      } else {
        c;
      }
    )
  );

let getBoardWithElements = (board: board, elements: list(boardElement)) => {
  let rec aux = (elements, acc) =>
    switch (elements) {
    | [] => acc
    | [he, ...re] => aux(re, getBoardWithElement(acc, he))
    };
  aux(elements, board);
};

let pathFromXY = (x, y, direction) => {
  coord: {
    x,
    y,
  },
  direction,
};

let getXPath = (c1, c2) => {
  let rec aux = (x1, x2, acc) =>
    if (x1 == x2) {
      acc;
    } else if (x1 < x2) {
      let nextX = x1 + 1;
      aux(nextX, x2, acc @ [pathFromXY(nextX, c1.y, Right)]);
    } else {
      let nextX = x1 - 1;
      aux(nextX, x2, acc @ [pathFromXY(nextX, c1.y, Left)]);
    };
  aux(c1.x, c2.x, []);
};

let getYPath = (c1, c2) => {
  let rec aux = (y1, y2, acc) =>
    if (y1 == y2) {
      acc;
    } else if (y1 < y2) {
      let nextY = y1 + 1;
      aux(nextY, y2, acc @ [pathFromXY(c1.x, nextY, Down)]);
    } else {
      let nextY = y1 - 1;
      aux(nextY, y2, acc @ [pathFromXY(c1.x, nextY, Up)]);
    };
  aux(c1.y, c2.y, []);
};

let findPath = (c1: coord, c2: coord) => {
  let rec aux = (start, stop, acc) =>
    if (start <=> stop) {
      acc;
    } else if (start.x != stop.x) {
      aux({...start, x: stop.x}, stop, acc @ getXPath(start, stop));
    } else {
      aux({...start, y: stop.y}, stop, acc @ getYPath(start, stop));
    };
  aux(c1, c2, []);
};

let pathToBoardElements = path => {
  let rec aux = (p, acc) =>
    switch (p) {
    | [] => acc
    | [ph, ...pr] => aux(pr, [Path(ph), ...acc])
    };
  aux(path, []);
};

let coordIsPathArrival = (path: path, coord) =>
  switch (Belt.List.get(path, Belt.List.length(path) - 1)) {
  | None => true
  | Some(p) => p.coord <=> coord
  };
