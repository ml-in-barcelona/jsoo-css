module type API = {
  type t;
  let toJson: array(Css.rule) => t;
  let mergeStyles: (. array(string)) => string;
  let injectRules: (. string, t) => unit;
  let injectRaw: (. string) => unit;
  let make: (. t) => string;
  let global: (. string, array(Css.rule)) => unit;
  /* let makeKeyFrames: (. t) => string; */
};

module Make = (Implementation: API) => {
  type t = Implementation.t;
  let merge = (. stylenames) => Implementation.mergeStyles(. stylenames);

  let insertRule = (. rule) => Implementation.injectRaw(. rule);

  let make =
    (. rules) => Implementation.make(. Implementation.toJson(rules));

  let global =
     (. selector, rules) =>
        Implementation.injectRules(. selector, Implementation.toJson(rules));

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
