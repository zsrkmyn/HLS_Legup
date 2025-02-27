# TCL File Generated by University of Toronto's LegUp group
# DO NOT MODIFY

# +-----------------------------------
# | Specify required package(s) 
# | 
package require -exact qsys 13.0
# | 
# +-----------------------------------


# +-----------------------------------
# | module tiger_icache
# | 
set_module_property DESCRIPTION "Tiger Instruction Cache"
set_module_property NAME tiger_icache
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property GROUP "LegUp/Memory"
set_module_property AUTHOR "University of Cambridge"
set_module_property DISPLAY_NAME "Tiger Instruction Cache"
#set_module_property DATASHEET_URL "doc/tiger_icache.pdf"
#set_module_property TOP_LEVEL_HDL_FILE tiger_icache_av_1port.v
#set_module_property TOP_LEVEL_HDL_MODULE tiger_icache_av_1port
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE false
set_module_property ANALYZE_HDL false
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false
# | 
# +-----------------------------------

# +-----------------------------------
# | file sets
# | 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL tiger_icache_av_1port
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file tiger_icache.v VERILOG PATH hdl/tiger_icache.v
add_fileset_file tiger_icache_av_1port.v VERILOG PATH hdl/tiger_icache_av_1port.v TOP_LEVEL_FILE
add_fileset_file tiger_icache_memory.v VERILOG PATH hdl/tiger_icache_memory.v
add_fileset_file tiger_icache_mux_param.v VERILOG PATH hdl/tiger_icache_mux_param.v
add_fileset_file tiger_icache_parameters.v VERILOG PATH hdl/tiger_icache_parameters.v

add_fileset SIM_VERILOG SIM_VERILOG "" ""
set_fileset_property SIM_VERILOG TOP_LEVEL tiger_icache_av_1port
set_fileset_property SIM_VERILOG ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file tiger_icache.v VERILOG PATH hdl/tiger_icache.v
add_fileset_file tiger_icache_av_1port.v VERILOG PATH hdl/tiger_icache_av_1port.v
add_fileset_file tiger_icache_memory.v VERILOG PATH hdl/tiger_icache_memory.v
add_fileset_file tiger_icache_mux_param.v VERILOG PATH hdl/tiger_icache_mux_param.v
add_fileset_file tiger_icache_parameters.v VERILOG PATH hdl/tiger_icache_parameters.v

add_fileset SIM_VHDL SIM_VHDL "" ""
set_fileset_property SIM_VHDL TOP_LEVEL tiger_icache_av_1port
set_fileset_property SIM_VHDL ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file tiger_icache.v VERILOG PATH hdl/tiger_icache.v
add_fileset_file tiger_icache_av_1port.v VERILOG PATH hdl/tiger_icache_av_1port.v
add_fileset_file tiger_icache_memory.v VERILOG PATH hdl/tiger_icache_memory.v
add_fileset_file tiger_icache_mux_param.v VERILOG PATH hdl/tiger_icache_mux_param.v
add_fileset_file tiger_icache_parameters.v VERILOG PATH hdl/tiger_icache_parameters.v
# | 
# +-----------------------------------

# +-----------------------------------
# | parameters
# | 
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point clock
# | 
add_interface clock clock end
set_interface_property clock clockRate 0
set_interface_property clock ENABLED true
set_interface_property clock EXPORT_OF ""
set_interface_property clock PORT_NAME_MAP ""
set_interface_property clock SVD_ADDRESS_GROUP ""

add_interface_port clock clk clk Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point reset
# | 
add_interface reset reset end
set_interface_property reset associatedClock clock
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset_n reset_n Input 1
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point icache_slave
# | 
add_interface icache_slave avalon end
set_interface_property icache_slave addressUnits WORDS
set_interface_property icache_slave associatedClock clock
set_interface_property icache_slave associatedReset reset
set_interface_property icache_slave bitsPerSymbol 8
set_interface_property icache_slave burstOnBurstBoundariesOnly false
set_interface_property icache_slave burstcountUnits WORDS
set_interface_property icache_slave explicitAddressSpan 0
set_interface_property icache_slave holdTime 0
set_interface_property icache_slave linewrapBursts false
set_interface_property icache_slave maximumPendingReadTransactions 4
set_interface_property icache_slave readLatency 0
set_interface_property icache_slave readWaitTime 1
set_interface_property icache_slave setupTime 0
set_interface_property icache_slave timingUnits Cycles
set_interface_property icache_slave writeWaitTime 0
set_interface_property icache_slave ENABLED true
set_interface_property icache_slave EXPORT_OF ""
set_interface_property icache_slave PORT_NAME_MAP ""
set_interface_property icache_slave SVD_ADDRESS_GROUP ""

add_interface_port icache_slave avs_icache_slave_address address Input 30
add_interface_port icache_slave avs_icache_slave_read read Input 1
add_interface_port icache_slave avs_icache_slave_readdata readdata Output 32
add_interface_port icache_slave avs_icache_slave_readdatavalid readdatavalid Output 1
add_interface_port icache_slave avs_icache_slave_waitrequest waitrequest Output 1
set_interface_assignment icache_slave embeddedsw.configuration.isFlash 0
set_interface_assignment icache_slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment icache_slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment icache_slave embeddedsw.configuration.isPrintableDevice 0
# | 
# +-----------------------------------

# +-----------------------------------
# | connection point icache_master
# | 
add_interface icache_master avalon start
set_interface_property icache_master addressUnits SYMBOLS
set_interface_property icache_master associatedClock clock
set_interface_property icache_master associatedReset reset
set_interface_property icache_master bitsPerSymbol 8
set_interface_property icache_master burstOnBurstBoundariesOnly false
set_interface_property icache_master burstcountUnits WORDS
set_interface_property icache_master doStreamReads false
set_interface_property icache_master doStreamWrites false
set_interface_property icache_master holdTime 0
set_interface_property icache_master linewrapBursts false
set_interface_property icache_master maximumPendingReadTransactions 0
set_interface_property icache_master readLatency 0
set_interface_property icache_master readWaitTime 1
set_interface_property icache_master setupTime 0
set_interface_property icache_master timingUnits Cycles
set_interface_property icache_master writeWaitTime 0
set_interface_property icache_master ENABLED true
set_interface_property icache_master EXPORT_OF ""
set_interface_property icache_master PORT_NAME_MAP ""
set_interface_property icache_master SVD_ADDRESS_GROUP ""

add_interface_port icache_master avm_icache_master_readdata readdata Input 32
add_interface_port icache_master avm_icache_master_readdatavalid readdatavalid Input 1
add_interface_port icache_master avm_icache_master_waitrequest waitrequest Input 1
add_interface_port icache_master avm_icache_master_address address Output 32
add_interface_port icache_master avm_icache_master_beginbursttransfer beginbursttransfer Output 1
add_interface_port icache_master avm_icache_master_burstcount burstcount Output 6
add_interface_port icache_master avm_icache_master_read read Output 1
# | 
# +-----------------------------------
