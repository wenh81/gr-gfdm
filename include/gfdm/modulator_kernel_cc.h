/* -*- c++ -*- */
/* 
 * Copyright 2016 Johannes Demel.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_GFDM_MODULATOR_KERNEL_CC_H
#define INCLUDED_GFDM_MODULATOR_KERNEL_CC_H

#include <complex>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <fftw3.h>
#include <stdexcept>

namespace gr {
  namespace gfdm {


    /*!
     * \brief modulate a GFDM block.
     *  This class initializes and performs all operations necessary to modulate a GFDM block.
     *
     */
    class modulator_kernel_cc
    {
    public:
      typedef std::complex<float> gfdm_complex;
      typedef boost::shared_ptr<modulator_kernel_cc> sptr;

      modulator_kernel_cc(int n_timeslots, int n_subcarriers, int overlap, std::vector<gfdm_complex> frequency_taps);
      ~modulator_kernel_cc();
      void generic_work(gfdm_complex* p_out, const gfdm_complex* p_in);
      int block_size(){return d_n_subcarriers * d_n_timeslots;};
      std::vector<gfdm_complex> filter_taps();

    private:
      int d_n_timeslots;
      int d_n_subcarriers;
      int d_ifft_len;
      int d_overlap;
      gfdm_complex* d_filter_taps;

      fftwf_plan initialize_fft(gfdm_complex* out_buf, gfdm_complex* in_buf, const int fft_size, bool forward);
      void initialize_taps_vector(gfdm_complex* filter_taps, std::vector<gfdm_complex> frequency_taps, const int n_timeslots);

      gfdm_complex* d_sub_fft_in;
      gfdm_complex* d_sub_fft_out;
      fftwf_plan d_sub_fft_plan;
      gfdm_complex* d_filtered;
      gfdm_complex* d_ifft_in;
      gfdm_complex* d_ifft_out;
      fftwf_plan d_ifft_plan;

      // DEBUG function
      const void print_vector(const gfdm_complex* v, const int size);
      static bool complex_compare(gfdm_complex i, gfdm_complex j) { return std::abs(i) < std::abs(j); };

    };

  } // namespace gfdm
} // namespace gr

#endif /* INCLUDED_GFDM_MODULATOR_KERNEL_CC_H */

