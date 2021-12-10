--Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2020.2.2 (lin64) Build 3118627 Tue Feb  9 05:13:49 MST 2021
--Date        : Wed Oct 27 12:00:31 2021
--Host        : volo-System-Product-Name running 64-bit Ubuntu 18.04.6 LTS
--Command     : generate_target zusys_wrapper.bd
--Design      : zusys_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_wrapper is
  port (
    PHY_LED : in STD_LOGIC_VECTOR ( 2 downto 0 );
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK3_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK3_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    TEST_IN : in STD_LOGIC_VECTOR ( 0 to 0 );
    TEST_OUT : out STD_LOGIC_VECTOR ( 0 to 0 );
    x0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    x1 : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    PHY_LED : in STD_LOGIC_VECTOR ( 2 downto 0 );
    TEST_IN : in STD_LOGIC_VECTOR ( 0 to 0 );
    TEST_OUT : out STD_LOGIC_VECTOR ( 0 to 0 );
    x0 : out STD_LOGIC_VECTOR ( 0 to 0 );
    x1 : out STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK3_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK3_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys;
begin
zusys_i: component zusys
     port map (
      PHY_LED(2 downto 0) => PHY_LED(2 downto 0),
      SI5338_CLK0_D_clk_n(0) => SI5338_CLK0_D_clk_n(0),
      SI5338_CLK0_D_clk_p(0) => SI5338_CLK0_D_clk_p(0),
      SI5338_CLK3_D_clk_n(0) => SI5338_CLK3_D_clk_n(0),
      SI5338_CLK3_D_clk_p(0) => SI5338_CLK3_D_clk_p(0),
      TEST_IN(0) => TEST_IN(0),
      TEST_OUT(0) => TEST_OUT(0),
      x0(0) => x0(0),
      x1(0) => x1(0)
    );
end STRUCTURE;
