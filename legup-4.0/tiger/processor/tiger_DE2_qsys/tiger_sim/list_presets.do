onerr {resume}
add list -bin /test_bench/clk
add list -hex /test_bench/DUT/the_sdram/az_addr
add list -hex /test_bench/DUT/the_sdram/az_be_n
add list -bin /test_bench/DUT/the_sdram/az_cs
add list -hex /test_bench/DUT/the_sdram/az_data
add list -bin /test_bench/DUT/the_sdram/az_rd_n
add list -bin /test_bench/DUT/the_sdram/az_wr_n
add list -bin /test_bench/DUT/the_sdram/clk
add list -hex /test_bench/DUT/the_sdram/za_data
add list -bin /test_bench/DUT/the_sdram/za_valid
add list -bin /test_bench/DUT/the_sdram/za_waitrequest
add list -asc /test_bench/DUT/the_sdram/CODE
add list -hex /test_bench/DUT/the_sdram/zs_addr
add list -hex /test_bench/DUT/the_sdram/zs_ba
add list -hex /test_bench/DUT/the_sdram/zs_cs_n
add list -bin /test_bench/DUT/the_sdram/zs_ras_n
add list -bin /test_bench/DUT/the_sdram/zs_cas_n
add list -bin /test_bench/DUT/the_sdram/zs_we_n
add list -hex /test_bench/DUT/the_sdram/zs_dq
add list -hex /test_bench/DUT/the_sdram/zs_dqm
add list -bin /test_bench/DUT/the_uart_0/chipselect
add list -hex /test_bench/DUT/the_uart_0/address
add list -hex /test_bench/DUT/the_uart_0/writedata
add list -hex /test_bench/DUT/the_uart_0/readdata
add list -bin /test_bench/DUT/the_uart_0/tx_ready
add list -asc /test_bench/DUT/the_uart_0/tx_data
add list -bin /test_bench/DUT/the_uart_0/rx_char_ready
add list -asc /test_bench/DUT/the_uart_0/rx_data
configure list -usestrobe 0
configure list -strobestart {0 ps} -strobeperiod {0 ps}
configure list -delta none
configure list -usegating 1
configure list -gateexpr { /test_bench/clk'rising }