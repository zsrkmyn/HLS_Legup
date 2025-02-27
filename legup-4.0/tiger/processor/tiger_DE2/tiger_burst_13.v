//Legal Notice: (C)2011 Altera Corporation. All rights reserved.  Your
//use of Altera Corporation's design tools, logic functions and other
//software and tools, and its AMPP partner logic functions, and any
//output files any of the foregoing (including device programming or
//simulation files), and any associated documentation or information are
//expressly subject to the terms and conditions of the Altera Program
//License Subscription Agreement or other applicable license agreement,
//including, without limitation, that your use is for the sole purpose
//of programming logic devices manufactured by Altera and sold by Altera
//or its authorized distributors.  Please refer to the applicable
//agreement for further details.

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

//
//Burst adapter parameters:
//adapter is mastered by: data_cache_0/dataMaster
//adapter masters: tiger_top_0/debugSlave
//asp_debug: 0
//byteaddr_width: 1
//ceil_data_width: 8
//data_width: 8
//dbs_shift: 2
//dbs_upstream_burstcount_width: 5
//downstream_addr_shift: 0
//downstream_burstcount_width: 1
//downstream_max_burstcount: 1
//downstream_pipeline: 0
//dynamic_slave: 1
//master_always_burst_max_burst: 0
//master_burst_on_burst_boundaries_only: 0
//master_data_width: 32
//master_interleave: 0
//master_linewrap_bursts: 0
//nativeaddr_width: 1
//slave_always_burst_max_burst: 0
//slave_burst_on_burst_boundaries_only: 0
//slave_interleave: 0
//slave_linewrap_bursts: 0
//upstream_burstcount: upstream_burstcount
//upstream_burstcount_width: 3
//upstream_max_burstcount: 4
//zero_address_width: 1


module tiger_burst_13 (
                        // inputs:
                         clk,
                         downstream_readdata,
                         downstream_readdatavalid,
                         downstream_waitrequest,
                         reset_n,
                         upstream_address,
                         upstream_burstcount,
                         upstream_byteenable,
                         upstream_debugaccess,
                         upstream_nativeaddress,
                         upstream_read,
                         upstream_write,
                         upstream_writedata,

                        // outputs:
                         downstream_arbitrationshare,
                         downstream_burstcount,
                         downstream_byteenable,
                         downstream_debugaccess,
                         downstream_read,
                         downstream_write,
                         downstream_writedata,
                         upstream_readdata,
                         upstream_readdatavalid,
                         upstream_waitrequest
                      )
;

  output  [  4: 0] downstream_arbitrationshare;
  output           downstream_burstcount;
  output           downstream_byteenable;
  output           downstream_debugaccess;
  output           downstream_read;
  output           downstream_write;
  output  [  7: 0] downstream_writedata;
  output  [  7: 0] upstream_readdata;
  output           upstream_readdatavalid;
  output           upstream_waitrequest;
  input            clk;
  input   [  7: 0] downstream_readdata;
  input            downstream_readdatavalid;
  input            downstream_waitrequest;
  input            reset_n;
  input            upstream_address;
  input   [  2: 0] upstream_burstcount;
  input            upstream_byteenable;
  input            upstream_debugaccess;
  input            upstream_nativeaddress;
  input            upstream_read;
  input            upstream_write;
  input   [  7: 0] upstream_writedata;

  wire    [  3: 0] address_offset;
  reg              atomic_counter;
  wire             current_upstream_address;
  wire    [  2: 0] current_upstream_burstcount;
  wire             current_upstream_read;
  wire             current_upstream_write;
  reg     [  4: 0] data_counter;
  wire    [  4: 0] dbs_adjusted_upstream_burstcount;
  wire             downstream_address;
  wire             downstream_address_base;
  wire    [  4: 0] downstream_arbitrationshare;
  wire             downstream_burstcount;
  wire             downstream_burstdone;
  wire             downstream_byteenable;
  wire             downstream_debugaccess;
  wire             downstream_nativeaddress;
  reg              downstream_read;
  wire             downstream_write;
  reg              downstream_write_reg;
  wire    [  7: 0] downstream_writedata;
  wire             enable_state_change;
  wire             fifo_empty;
  wire             max_burst_size;
  wire             p1_atomic_counter;
  wire             p1_fifo_empty;
  wire             p1_state_busy;
  wire             p1_state_idle;
  wire             pending_register_enable;
  wire             pending_upstream_read;
  reg              pending_upstream_read_reg;
  wire             pending_upstream_write;
  reg              pending_upstream_write_reg;
  reg     [  3: 0] read_address_offset;
  wire             read_update_count;
  wire    [  4: 0] read_write_dbs_adjusted_upstream_burstcount;
  reg     [  4: 0] registered_read_write_dbs_adjusted_upstream_burstcount;
  reg              registered_upstream_address;
  reg     [  2: 0] registered_upstream_burstcount;
  reg              registered_upstream_byteenable;
  reg              registered_upstream_nativeaddress;
  reg              registered_upstream_read;
  reg              registered_upstream_write;
  reg              state_busy;
  reg              state_idle;
  wire             sync_nativeaddress;
  wire    [  4: 0] transactions_remaining;
  reg     [  4: 0] transactions_remaining_reg;
  wire             update_count;
  wire             upstream_burstdone;
  wire             upstream_read_run;
  wire    [  7: 0] upstream_readdata;
  wire             upstream_readdatavalid;
  wire             upstream_waitrequest;
  wire             upstream_write_run;
  reg     [  3: 0] write_address_offset;
  wire             write_update_count;
  assign sync_nativeaddress = |upstream_nativeaddress;
  //downstream, which is an e_avalon_master
  //upstream, which is an e_avalon_slave
  assign upstream_burstdone = current_upstream_read ? (transactions_remaining == downstream_burstcount) & downstream_read & ~downstream_waitrequest : (transactions_remaining == (atomic_counter + 1)) & downstream_write & ~downstream_waitrequest;
  assign p1_atomic_counter = atomic_counter + (downstream_read ? downstream_burstcount : 1);
  assign downstream_burstdone = (downstream_read | downstream_write) & ~downstream_waitrequest & (p1_atomic_counter == downstream_burstcount);
  assign dbs_adjusted_upstream_burstcount = pending_register_enable ? read_write_dbs_adjusted_upstream_burstcount : registered_read_write_dbs_adjusted_upstream_burstcount;
  assign read_write_dbs_adjusted_upstream_burstcount = {upstream_burstcount,
    2'b00};

  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          registered_read_write_dbs_adjusted_upstream_burstcount <= 0;
      else if (pending_register_enable)
          registered_read_write_dbs_adjusted_upstream_burstcount <= read_write_dbs_adjusted_upstream_burstcount;
    end


  assign p1_state_idle = state_idle & ~upstream_read & ~upstream_write | state_busy & (data_counter == 0) & p1_fifo_empty & ~pending_upstream_read & ~pending_upstream_write;
  assign p1_state_busy = state_idle & (upstream_read | upstream_write) | state_busy & (~(data_counter == 0) | ~p1_fifo_empty | pending_upstream_read | pending_upstream_write);
  assign enable_state_change = ~(downstream_read | downstream_write) | ~downstream_waitrequest;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          pending_upstream_read_reg <= 0;
      else if (upstream_read & state_idle)
          pending_upstream_read_reg <= -1;
      else if (upstream_burstdone)
          pending_upstream_read_reg <= 0;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          pending_upstream_write_reg <= 0;
      else if (upstream_burstdone)
          pending_upstream_write_reg <= 0;
      else if (upstream_write & (state_idle | ~upstream_waitrequest))
          pending_upstream_write_reg <= -1;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          state_idle <= 1;
      else if (enable_state_change)
          state_idle <= p1_state_idle;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          state_busy <= 0;
      else if (enable_state_change)
          state_busy <= p1_state_busy;
    end


  assign pending_upstream_read = pending_upstream_read_reg;
  assign pending_upstream_write = pending_upstream_write_reg & ~upstream_burstdone;
  assign pending_register_enable = state_idle | ((upstream_read | upstream_write) & ~upstream_waitrequest);
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          registered_upstream_read <= 0;
      else if (pending_register_enable)
          registered_upstream_read <= upstream_read;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          registered_upstream_write <= 0;
      else if (pending_register_enable)
          registered_upstream_write <= upstream_write;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          registered_upstream_burstcount <= 0;
      else if (pending_register_enable)
          registered_upstream_burstcount <= upstream_burstcount;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          registered_upstream_address <= 0;
      else if (pending_register_enable)
          registered_upstream_address <= upstream_address;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          registered_upstream_nativeaddress <= 0;
      else if (pending_register_enable)
          registered_upstream_nativeaddress <= upstream_nativeaddress;
    end


  assign current_upstream_read = registered_upstream_read & !downstream_write;
  assign current_upstream_write = registered_upstream_write;
  assign current_upstream_address = registered_upstream_address;
  assign current_upstream_burstcount = pending_register_enable ? upstream_burstcount : registered_upstream_burstcount;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          atomic_counter <= 0;
      else if ((downstream_read | downstream_write) & ~downstream_waitrequest)
          atomic_counter <= downstream_burstdone ? 0 : p1_atomic_counter;
    end


  assign read_update_count = current_upstream_read & ~downstream_waitrequest;
  assign write_update_count = current_upstream_write & downstream_write & downstream_burstdone;
  assign update_count = read_update_count | write_update_count;
  assign transactions_remaining = (state_idle & (upstream_read | upstream_write)) ? dbs_adjusted_upstream_burstcount : transactions_remaining_reg;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          transactions_remaining_reg <= 0;
      else 
        transactions_remaining_reg <= (state_idle & (upstream_read | upstream_write)) ? dbs_adjusted_upstream_burstcount : update_count ? transactions_remaining_reg - downstream_burstcount : transactions_remaining_reg;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          data_counter <= 0;
      else 
        data_counter <= state_idle & upstream_read & ~upstream_waitrequest ?  dbs_adjusted_upstream_burstcount : downstream_readdatavalid ? data_counter - 1 : data_counter;
    end


  assign max_burst_size = 1;
  assign downstream_burstcount = (transactions_remaining > max_burst_size) ? max_burst_size : transactions_remaining;
  assign downstream_arbitrationshare = current_upstream_read ? (dbs_adjusted_upstream_burstcount) : dbs_adjusted_upstream_burstcount;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          write_address_offset <= 0;
      else 
        write_address_offset <= state_idle & upstream_write ? 0 : ((downstream_write & ~downstream_waitrequest & downstream_burstdone)) ? write_address_offset + downstream_burstcount : write_address_offset;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          read_address_offset <= 0;
      else 
        read_address_offset <= state_idle & upstream_read ? 0 : (downstream_read & ~downstream_waitrequest) ? read_address_offset + downstream_burstcount : read_address_offset;
    end


  assign downstream_nativeaddress = registered_upstream_nativeaddress >> 2;
  assign address_offset = current_upstream_read ? read_address_offset : write_address_offset;
  assign downstream_address_base = current_upstream_address;
  assign downstream_address = downstream_address_base + address_offset;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          downstream_read <= 0;
      else if (~downstream_read | ~downstream_waitrequest)
          downstream_read <= state_idle & upstream_read ? 1 : (transactions_remaining == downstream_burstcount) ? 0 : downstream_read;
    end


  assign upstream_readdatavalid = downstream_readdatavalid;
  assign upstream_readdata = downstream_readdata;
  assign fifo_empty = 1;
  assign p1_fifo_empty = 1;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          downstream_write_reg <= 0;
      else if (~downstream_write_reg | ~downstream_waitrequest)
          downstream_write_reg <= state_idle & upstream_write ? 1 : ((transactions_remaining == downstream_burstcount) & downstream_burstdone) ? 0 : downstream_write_reg;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          registered_upstream_byteenable <= 1'b1;
      else if (pending_register_enable)
          registered_upstream_byteenable <= upstream_byteenable;
    end


  assign downstream_write = downstream_write_reg & upstream_write & !downstream_read;
  assign downstream_byteenable = downstream_write_reg ? upstream_byteenable : registered_upstream_byteenable;
  assign downstream_writedata = upstream_writedata;
  assign upstream_read_run = state_idle & upstream_read;
  assign upstream_write_run = state_busy & upstream_write & ~downstream_waitrequest & !downstream_read;
  assign upstream_waitrequest = (upstream_read | current_upstream_read) ? ~upstream_read_run : current_upstream_write ? ~upstream_write_run : 1;
  assign downstream_debugaccess = upstream_debugaccess;

endmodule

