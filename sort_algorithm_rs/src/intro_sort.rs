use crate::{heap_sort::heap_sort_impl, quick_sort::chose_pivot};

pub fn intro_sort(vec: &mut Vec<i32>) {
  let max_depth = 2 * ((vec.len() as f64).log2() as usize);
  intro_sort_impl(vec, 0, vec.len() - 1, max_depth);
}

pub fn intro_sort_impl(vec: &mut Vec<i32>, l: usize, r: usize, max_depth: usize) {
  if r <= l {
    return;
  }

  if max_depth == 0 {
    heap_sort_impl(vec, l, r);
    return;
  }

  let p = chose_pivot(vec, l, r);

  if p > 0 {
    intro_sort_impl(vec, l, p - 1, max_depth - 1);
  }

  intro_sort_impl(vec, p, r, max_depth - 1);
}
