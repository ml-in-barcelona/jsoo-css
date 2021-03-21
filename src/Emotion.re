include Core;
include Colors;

include Core.Make({
  let mergeStyles = JsooEmotion.mergeStyles;
  let make = JsooEmotion.make;
  let injectRule = JsooEmotion.injectRule;
  let injectRaw = JsooEmotion.injectRaw;
  let makeKeyFrames = _ => "";
});
