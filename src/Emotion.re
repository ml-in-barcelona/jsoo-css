include Values;
include Properties;
include Colors;
include Core;

include Core.Make({
  type t = Js_of_ocaml.Js.json;
  let toJson = Css.toJson;
  let mergeStyles = Emotion_bindings.mergeStyles;
  let make = Emotion_bindings.make;
  let injectRule = Emotion_bindings.injectRule;
  let injectRaw = Emotion_bindings.injectRaw;
});
