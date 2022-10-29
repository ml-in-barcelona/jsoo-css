include Values;
include Properties;
include Colors;
include Core;

include Core.Make({
  type t = Js_of_ocaml.Js.json;
  let toJson = Css.toJson;
  let mergeStyles = Emotion_bindings.mergeStyles;
  let make = Emotion_bindings.make;
  let injectRules = Emotion_bindings.injectRules;
  let injectRaw = Emotion_bindings.injectRaw;
  let global =
    (. selector, rules) =>
      Emotion_bindings.injectRules(. selector, toJson(rules));
  let keyframe =
    (. frames) =>
      Emotion_bindings.keyframe(.
        Array.fold_left(
          (. dict, (stop, rules)) => {
            Js_of_ocaml.Js.Unsafe.set(
              dict,
              Int.to_string(stop) ++ "%",
              toJson(rules),
            );
            dict;
          },
          Js_of_ocaml.Js.Unsafe.obj([||]),
          frames,
        ),
      );
});
