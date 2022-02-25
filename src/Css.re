type rule =
  | Declaration(string, string)
  | Selector(string, array(rule))
  | Pseudoclass(string, array(rule))
  | PseudoclassParam(string, string, array(rule));

let rec ruleToDict = (dict: Js_of_ocaml.Js.json, rule) => {
  open Js_of_ocaml;
  switch (rule) {
  | Declaration(name, value) =>
    Js.Unsafe.set(dict, Js.string(name), Js.string(value))
  | Selector(name, ruleset) =>
    Js.Unsafe.set(dict, Js.string(name), toJson(ruleset))
  | Pseudoclass(name, ruleset) =>
    Js.Unsafe.set(dict, Js.string(":" ++ name), toJson(ruleset))
  | PseudoclassParam(name, param, ruleset) =>
    Js.Unsafe.set(
      dict,
      Js.string(":" ++ name ++ "(" ++ param ++ ")"),
      toJson(ruleset),
    )
  };
  dict;
}

and toJson = (rules: array(rule)) =>
  rules |> Array.fold_left(ruleToDict, Js_of_ocaml.Js.Unsafe.obj([||]));
