let log = v => Js_of_ocaml.Firebug.console##log(v);
let tap = (~name=?, v) => {
  switch (name) {
  | Some(n) => log(n)
  | None => ()
  };
  log(v);
  v;
};
