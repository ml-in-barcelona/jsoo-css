open Setup;
open Jsoo_css;
open Properties;

module Dict = {
  /* Dummy implementation of a dictionary */
  type item = (string, string);
  type t = array(item);
  let make = (): t => [||];
  let insert = (key, value, dict): t => {
    Array.append(dict, [|(key, value)|]);
  };
};

module CssForTest = {
  exception NotImplemented;
  include Core.Make({
    let mergeStyles = _ => raise(NotImplemented);
    let injectRule = _ => raise(NotImplemented);
    let injectRaw = _ => raise(NotImplemented);

    type t = Dict.t;

    let rec ruleToDict = (dict, rule) => {
      switch (rule) {
      | Css.Declaration(name, value) => dict |> Dict.insert(name, value)
      | _ => Dict.make()
      };
    }
    and toJson = (rules: array(Css.rule)): Dict.t =>
      rules |> Array.fold_left(ruleToDict, [||]);

    let make = dict =>
      dict
      |> Array.fold_left(
           (arr, (k, v)) => Array.append(arr, [|k ++ ": " ++ v|]),
           [||],
         )
      |> Array.to_list
      |> String.concat(";");
  });
};

let css = v => CssForTest.make([|v|]);

type testData = {
  name: string,
  cases: list((string, string)),
};

let jsooTestSuitData = [
  {
    name: "color",
    cases: [
      (css(color(rgb(1, 2, 3))), "color: rgb(1, 2, 3)"),
      (css(color(rgba(4, 5, 6, `num(0.3)))), "color: rgba(4, 5, 6, 0.3)"),
      (
        css(color(hsl(deg(7.), pct(8.), pct(9.)))),
        "color: hsl(7deg, 8%, 9%)",
      ),
      (
        css(color(hsla(deg(10.), pct(11.), pct(12.), `num(0.5)))),
        "color: hsla(10deg, 11%, 12%, 0.5)",
      ),
      (
        css(color(hsla(rad(4.7), pct(11.), pct(12.), pct(50.)))),
        "color: hsla(4.7rad, 11%, 12%, 50%)",
      ),
      (css(color(transparent)), "color: transparent"),
      (css(color(hex("FFF"))), "color: #FFF"),
      (css(color(currentColor)), "color: currentColor"),
    ],
  },
];

describe("Jsoo Test Suit", _ => {
  jsooTestSuitData
  |> List.iter(data => {
       describe(data.name, ({test, _}) => {
         data.cases
         |> List.iter(case => {
              let input = fst(case);
              let out = snd(case);
              test("should render " ++ input, ({expect, _}) => {
                expect.string(input).toEqual(out)
              });
            })
       })
     })
});
