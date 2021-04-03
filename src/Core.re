open Css;

let rec ruleToDict = (dict: Js_of_ocaml.Js.json, rule) => {
  open Js_of_ocaml;
  switch (rule) {
  | Declaration(name, value) =>
    Js.Unsafe.set(dict, Js.string(name), Js.string(value))
  | Selector(name, ruleset) =>
    Js.Unsafe.set(dict, Js.string(name), toJson(ruleset))
  | PseudoClass(name, ruleset) =>
    Js.Unsafe.set(dict, Js.string(":" ++ name), toJson(ruleset))
  | PseudoClassParam(name, param, ruleset) =>
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

module type API = {
  type t;
  let toJson: array(rule) => t;
  let mergeStyles: (. array(string)) => string;
  let injectRule: (. t) => unit;
  let injectRaw: (. string) => unit;
  let make: (. t) => string;
  /* let makeKeyFrames: (. t) => string; */
};

module Make = (Implementation: API) => {
  type t = Implementation.t;
  let merge = (. stylenames) => Implementation.mergeStyles(. stylenames);

  let insertRule = (. rule) => Implementation.injectRaw(. rule);

  let make =
    (. rules) => Implementation.make(. Implementation.toJson(rules));
  /* let global =
     (. selector, rules) =>
       Implementation.injectRule(.
         [|(selector, toJson(rules))|] |> Js.Unsafe.obj,
       ); */
  /* let keyframes =
     (. frames) =>
       Implementation.makeKeyFrames(.
         frames
         |> Array.fold_left(
              (. dict, (stop, rules)) => {
                Js.Unsafe.set(
                  dict,
                  Int.to_string(stop) ++ "%",
                  toJson(rules),
                );
                dict;
              },
              Js.Unsafe.obj([||]),
            ),
       ); */
};
