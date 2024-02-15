use std::env;
use std::error::Error;
use std::time;

#[allow(unused_imports)]
use sort_algorithm::{utils, *};

fn main() -> Result<(), Box<dyn Error>> {
  let args: Vec<String> = env::args().collect();
  let config = Config::new(&args);

  let mut sequence = utils::read_file(config.sequence_file)?;
  let answer = utils::read_file(config.answer_file)?;

  for e in sequence.iter() {
    print!("{} ", e);
  }
  println!("");

  let timer = time::Instant::now();

  sequence.sort();
  // sort_algorithm::quick_sort(&mut sequence);
  // sort_algorithm::intro_sort(&mut sequence);
  // sort_algorithm::merge_sort(&mut sequence);
  // sort_algorithm::bubble_sort(&mut sequence);
  // sort_algorithm::insertion_sort(&mut sequence);
  // sort_algorithm::selection_sort(&mut sequence);
  // sort_algorithm::heap_sort(&mut sequence);

  let elapsed = timer.elapsed();

  for e in sequence.iter() {
    print!("{} ", e);
  }
  println!("");

  if sequence != answer {
    eprintln!("failed to sort.");
  }

  println!("{:?}", elapsed);

  Ok(())
}

struct Config {
  sequence_file: String,
  answer_file: String,
}

impl Config {
  fn new(args: &[String]) -> Config {
    let sequence_file = args[1].clone();
    let answer_file = args[2].clone();

    Config {
      sequence_file,
      answer_file,
    }
  }
}
