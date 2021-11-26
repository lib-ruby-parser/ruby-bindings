mod fns;
mod fns_c;
mod fns_shared;

mod messages_h;
mod nodes_h;

mod messages_rb;
mod nodes_rb;

pub(crate) fn codegen() {
    messages_h::codegen();
    nodes_h::codegen();

    messages_rb::codegen();
    nodes_rb::codegen();
}
