use rand::Rng;
use std::env;
use std::error::Error;
use std::fs;
// use std::io::stdout;
use std::io::Write;

fn main() -> Result<(), Box<dyn Error>> {
  let args: Vec<String> = env::args().collect();

  let config = Config::new(&args)?;

  let mut answer: Vec<i32> = vec![];

  let mut rng = rand::thread_rng();

  let mut file = fs::File::create(config.sequence_file)?;

  for _ in 0..config.sequence_size {
    // if i == 0 || i == config.sequence_size - 1 || (i + 1) % 10000 == 0 {
    //   print!("\rgenerating... {}/{}", i + 1, config.sequence_size);
    //   stdout().flush().unwrap();
    // }

    let n = rng.gen::<i32>();
    writeln!(file, "{}", n)?;
    answer.push(n);
  }
  println!("");

  answer.sort();

  let mut file = fs::File::create(config.answer_file)?;

  // let mut i = 0;
  for e in answer.iter() {
    // if i == 0 || i == config.sequence_size - 1 || (i + 1) % 10000 == 0 {
    //   print!("\ranswer writing... {}/{}", i + 1, config.sequence_size);
    //   stdout().flush().unwrap();
    // }
    // i += 1;

    writeln!(file, "{}", e)?;
  }
  println!("");

  Ok(())
}

struct Config {
  sequence_size: usize,
  sequence_file: String,
  answer_file: String,
}

impl Config {
  fn new(args: &[String]) -> Result<Config, Box<dyn Error>> {
    if args.len() < 4 {}

    let sequence_size = args[1].clone().parse()?;
    let sequence_file = args[2].clone();
    let answer_file = args[3].clone();

    Ok(Config {
      sequence_size,
      sequence_file,
      answer_file,
    })
  }
}
