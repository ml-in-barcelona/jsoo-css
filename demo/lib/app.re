module Model = {
  [@deriving sexp_of]
  type t = {
    url: Router.url,
    page_home_model: Page_home.Model.t,
  };

  let cutoff =
      (
        {url: url_1, page_home_model: page_home_model_1},
        {url: url_2, page_home_model: page_home_model_2},
      ) =>
    Router.compare_url(url_1, url_2) == 0
    && Page_home.Model.cutoff(page_home_model_1, page_home_model_2);

  let update_url = (t, url) => {...t, url};

  let empty = () => {
    url: Router.current_url(),
    page_home_model: Page_home.Model.empty,
  };
};

module Action = {
  [@deriving sexp_of]
  type t =
    | UrlChange(Router.url)
    | Page_home_action(Page_home.Action.t);

  let apply = (model, action, _state, ~schedule_action): Model.t =>
    switch (action) {
    | UrlChange(url) => Model.update_url(model, url)
    | Page_home_action(action) => {
        ...model,
        page_home_model:
          Page_home.Action.apply(
            model.Model.page_home_model, action, (), ~schedule_action=action =>
            schedule_action(Page_home_action(action))
          ),
      }
    };
};

module State = {
  [@deriving (sexp_of, fields)]
  type t = {schedule: Action.t => unit};
};

let on_startup = (~schedule_action as schedule, _) => {
  let state = {State.schedule: schedule};
  let _event =
    Router.on_url_change(~f=loc => schedule(Action.UrlChange(loc)));

  Async_kernel.return(state);
};

let on_display = (~old_model as _, _, ~schedule_action as _) => ();

let view = (model, ~inject) => {
  open Incr_dom.Incr.Let_syntax;
  let%map model = model;
  switch (Router.route_of_url(model.Model.url)) {
  | Some(Home) =>
    Page_home.view(model.page_home_model, ~inject=action =>
      inject(Action.Page_home_action(action))
    )
  | None => Page_not_found.view()
  };
};

let create = (model, ~old_model, ~inject) => {
  open Incr_dom.Incr.Let_syntax;
  let%map apply_action = {
    let%map model = model;
    Action.apply(model);
  }
  and on_display = {
    let%map old_model = old_model;
    on_display(~old_model);
  }
  and view = view(model, ~inject)
  and model = model;
  Incr_dom.Component.create(
    ~apply_action,
    ~on_display,
    model,
    Incr_dom.Tyxml.Html.toelt(view),
  );
};
