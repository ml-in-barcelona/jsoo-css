type t =
  | Home;

let from_url: list(string) => option(t);

let to_string: t => string;