/* Address: ram:00008cbc; name: FUN_ram_00008cbc; body bytes: 26 */

char * FUN_ram_00008cbc(char *param_1,char param_2,int param_3)

{
  char *pcVar1;
  
  gp = &DAT_ram_20002000;
  pcVar1 = param_1 + param_3;
  while( true ) {
    if (param_1 == pcVar1) {
      return (char *)0x0;
    }
    if (*param_1 == param_2) break;
    param_1 = param_1 + 1;
  }
  gp = &DAT_ram_20002000;
  return param_1;
}

