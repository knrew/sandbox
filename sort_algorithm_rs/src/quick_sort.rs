pub fn quick_sort(vec: &mut Vec<i32>) {
  // quick_sort_recursive(vec, 0, vec.len() - 1);
  quick_sort_norecursive(vec);
}

#[allow(dead_code)]
fn quick_sort_recursive(vec: &mut Vec<i32>, l: usize, r: usize) {
  if l >= r {
    return;
  }

  let p = chose_pivot(vec, l, r);

  if p > 0 {
    quick_sort_recursive(vec, l, p - 1);
  }

  quick_sort_recursive(vec, p + 1, r);
}

#[allow(dead_code)]
fn quick_sort_norecursive(vec: &mut Vec<i32>) {
  let mut st: Vec<(usize, usize)> = vec![];

  st.push((0, vec.len() - 1));

  while !st.is_empty() {
    let (l, r) = st.pop().unwrap();

    if l < r {
      let p = chose_pivot(vec, l, r);

      if 2 * p < r + l {
        st.push((p + 1, r));
        if p > 0 {
          st.push((l, p - 1));
        }
      } else {
        if p > 0 {
          st.push((l, p - 1));
        }
        st.push((p + 1, r));
      }
    }
  }
}

fn chose_pivot(vec: &mut Vec<i32>, l: usize, r: usize) -> usize {
  let pivot = vec[r];

  let mut i = l;
  let mut j = r - 1;

  loop {
    while vec[i] < pivot {
      i += 1;
    }

    while i < j && pivot < vec[j] {
      j -= 1;
    }

    if i >= j {
      break;
    }

    vec.swap(i, j);
  }

  vec.swap(i, r);

  i
}
