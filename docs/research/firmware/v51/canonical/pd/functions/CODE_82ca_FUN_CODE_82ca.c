/* Address: CODE:82ca; name: FUN_CODE_82ca; body bytes: 12 */

char FUN_CODE_82ca(char param_1,char param_2)

{
  char in_PSW;
  
  return DAT_EXTMEM_04a3 -
         (param_1 - (((DAT_EXTMEM_04a4 < (byte)(param_2 - (in_PSW >> 7))) << 7) >> 7));
}

