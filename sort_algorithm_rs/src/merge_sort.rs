#[allow(unused_imports)]
use std::collections::LinkedList;

pub fn merge_sort(vec: &mut Vec<i32>) {
  merge_sort_array(vec, 0, vec.len() - 1);
  // merge_sort_linked_list(vec);
}

#[allow(dead_code)]
fn merge_sort_array(vec: &mut Vec<i32>, l: usize, r: usize) {
  if l >= r {
    return;
  }

  let mid = l + (r - l) / 2;

  merge_sort_array(vec, l, mid);
  merge_sort_array(vec, mid + 1, r);

  let mut vec_tmp: Vec<i32> = vec![0; vec.len()];

  for i in l..mid + 1 {
    vec_tmp[i] = vec[i];
  }

  let mut i = mid + 1;
  let mut j = r;
  while i <= r {
    vec_tmp[i] = vec[j];
    i += 1;
    j -= 1;
  }

  let mut i = l;
  let mut j = r;
  for k in l..r + 1 {
    if vec_tmp[i] <= vec_tmp[j] {
      vec[k] = vec_tmp[i];
      i += 1;
    } else {
      vec[k] = vec_tmp[j];
      j -= 1;
    }
  }
}

#[allow(dead_code)]
fn merge_sort_linked_list(_vec: &mut Vec<i32>) {}
