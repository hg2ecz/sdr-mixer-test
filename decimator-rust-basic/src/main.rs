use num_complex::Complex;
use std::time;

mod decimator;

const ITERATION: i32 = 1000;

fn main() {
    let mut samplein: Vec<Complex<f32>> = Vec::new();
    for i in 0..100_000 {
        samplein.push(Complex::new(1., 1. + 1./i as f32));
    }
    let samplerate = 2_400_000;
    let decimfactor = 10;
    let transition_bw = 0.051;
    let window = decimator::Window::Hamming;
    let mut decim = decimator::Decimator::new(samplerate, decimfactor, transition_bw, window);
    decim.setfreq(100_000., false);

    let mut sumsamplein = 0;
    let mut sumsampleout = 0;

    let now = time::Instant::now();
    for _i in 0..ITERATION {
        let sampleout = decim.decimator(&samplein);
        sumsamplein += samplein.len();
        sumsampleout += sampleout.len();

    }
    let elapsed_msec = now.elapsed().as_millis() as f64;
    eprintln!("Decimator(10) inspeed: {:.1} Msps", sumsamplein as f64/elapsed_msec/1000.);
    eprintln!("Decimator(10) outspeed: {:.1} Msps", sumsampleout as f64/elapsed_msec/1000.);
}
