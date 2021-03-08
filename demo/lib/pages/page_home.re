module Model = {
  [@deriving sexp_of]
  type t = {greet_model: Greet.Model.t};

  let cutoff = ({greet_model: greet_model_1}, {greet_model: greet_model_2}) =>
    Greet.Model.cutoff(greet_model_1, greet_model_2);

  let empty = {greet_model: Greet.Model.empty};
};

module State = {
  [@deriving sexp_of]
  type t = unit;
};

module Action = {
  [@deriving sexp_of]
  type t =
    | Greet_action(Greet.Action.t);

  let apply = (model, action, _state, ~schedule_action) =>
    switch (action) {
    | Greet_action(action) =>
      Model.{
        greet_model:
          Greet.Action.apply(
            model.greet_model, action, (), ~schedule_action=action =>
            schedule_action(Greet_action(action))
          ),
      }
    };
};

let on_startup = (~schedule_action as _, _) => Async_kernel.return();

let view = (model, ~inject) =>
  Incr_dom.Tyxml.Html.(
    div([
      Greet.view(model.Model.greet_model, ~inject=action =>
        inject(Action.Greet_action(action))
      ),
    ])
  );

let create = (model, ~old_model as _, ~inject) => {
  open Incr_dom;
  let%map.Incr model = model;
  let view = view(model, ~inject);
  Component.create(
    model,
    Tyxml.Html.toelt(view),
    ~apply_action=Action.apply(model),
  );
};