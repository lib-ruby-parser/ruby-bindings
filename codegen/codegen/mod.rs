mod fns;
mod fns_c;
mod fns_shared;

mod messages_h;
mod nodes_h;

pub(crate) fn codegen() {
    messages_h::codegen();
    nodes_h::codegen();
}
