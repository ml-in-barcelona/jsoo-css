include Core;
include Values;
include Properties;
include Colors;

include Make({
  type t = Js_of_ocaml.Js.json;
  let toJson = Core.toJson;
  let mergeStyles = JsooEmotion.mergeStyles;
  let make = JsooEmotion.make;
  let injectRule = JsooEmotion.injectRule;
  let injectRaw = JsooEmotion.injectRaw;
});
