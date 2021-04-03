open Values;

/* Js_of_ocaml.URL clashes with Values.Url, here we specify we want the latest */
module Url = Values.Url;

type rule =
  | Declaration(string, string)
  | Selector(string, array(rule))
  | PseudoClass(string, array(rule))
  | PseudoClassParam(string, string, array(rule));

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

let concatArr = (f, separator, arr) =>
  arr |> Array.map(f) |> Array.to_list |> String.concat(separator);

module Converter = {
  let string_of_time = t => Int.to_string(t) ++ "ms";

  let string_of_content = x =>
    switch (x) {
    | #Content.t as c => Content.toString(c)
    | #Counter.t as c => Counter.toString(c)
    | #Counters.t as c => Counters.toString(c)
    | #Gradient.t as g => Gradient.toString(g)
    | #Url.t as u => Url.toString(u)
    | #Var.t as va => Var.toString(va)
    | #Cascading.t as c => Cascading.toString(c)
    };
  let string_of_counter_increment = x =>
    switch (x) {
    | #CounterIncrement.t as o => CounterIncrement.toString(o)
    | #Var.t as va => Var.toString(va)
    | #Cascading.t as c => Cascading.toString(c)
    };
  let string_of_counter_reset = x =>
    switch (x) {
    | #CounterReset.t as o => CounterReset.toString(o)
    | #Var.t as va => Var.toString(va)
    | #Cascading.t as c => Cascading.toString(c)
    };
  let string_of_counter_set = x =>
    switch (x) {
    | #CounterSet.t as o => CounterSet.toString(o)
    | #Var.t as va => Var.toString(va)
    | #Cascading.t as c => Cascading.toString(c)
    };

  let string_of_column_gap =
    fun
    | #ColumnGap.t as gcg => ColumnGap.toString(gcg)
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l)
    | #Var.t as va => Var.toString(va)
    | #Cascading.t as c => Cascading.toString(c);

  let string_of_position =
    fun
    | `auto => "auto"
    | #Length.t as l => Length.toString(l)
    | #Var.t as va => Var.toString(va)
    | #Cascading.t as c => Cascading.toString(c);

  let string_of_color =
    fun
    | #Color.t as co => Color.toString(co)
    | #Var.t as va => Var.toString(va);

  let string_of_dasharray =
    fun
    | #Percentage.t as p => Percentage.toString(p)
    | #Length.t as l => Length.toString(l);
};

include Converter;

let important = v =>
  switch (v) {
  | Declaration(name, value) => Declaration(name, value ++ " !important")
  | Selector(_, _)
  | PseudoClass(_, _)
  | PseudoClassParam(_, _, _) => v
  };

let label = label => Declaration("label", label);
