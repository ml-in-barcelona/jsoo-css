let () =
  Incr_dom.Start_app.start(
    ~bind_to_element_with_id="root",
    ~initial_model=Jsoo_css_demo.App.Model.empty(),
    (module Jsoo_css_demo.App),
  );
