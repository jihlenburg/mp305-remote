/* Address: ram:00051236; name: FUN_ram_00051236; body bytes: 212 */

int FUN_ram_00051236(undefined4 param_1,char *param_2,undefined4 param_3)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  gp = 0x20004000;
  pcVar1 = (char *)FUN_ram_20000040(0x10,0x53);
  iVar2 = FUN_ram_20000040(0x10,0x53);
  iVar3 = 0x13;
  if (pcVar1 != (char *)0x0) {
    if (iVar2 != 0) {
      tmos_memset(iVar2,0,0x10);
      iVar3 = LL_Encrypt(param_1,iVar2,pcVar1);
      if (iVar3 == 0) {
        if (*pcVar1 < '\0') {
          FUN_ram_000511d0(pcVar1,iVar2);
          FUN_ram_000511a8(iVar2,&DAT_ram_0006c0dc,param_2);
        }
        else {
          FUN_ram_000511d0(pcVar1,param_2);
        }
        if (*param_2 < '\0') {
          FUN_ram_000511d0(param_2,iVar2);
          FUN_ram_000511a8(iVar2,&DAT_ram_0006c0dc,param_3);
        }
        else {
          FUN_ram_000511d0(param_2,param_3);
        }
      }
    }
    FUN_ram_20000104(pcVar1);
  }
  if (iVar2 != 0) {
    FUN_ram_20000104(iVar2);
  }
  return iVar3;
}

