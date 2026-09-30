/* Address: 0002cb6c; name: FUN_0002cb6c; body bytes: 264 */

void FUN_0002cb6c(int param_1,int *param_2,int *param_3,int param_4,undefined4 param_5,code *param_6
                 )

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int local_44;
  ushort local_3e;
  ushort local_3c;
  short local_3a;
  short local_38;
  byte local_36;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  
  iVar2 = FUN_00051b26(param_5);
  if (iVar2 == 0) {
    FUN_00046a36(param_4,&local_44,param_5,0);
    uVar3 = (uint)local_3c;
    if ((uVar3 != 0) && (local_3e != 0)) {
      local_2c = *param_3 + (int)local_3a;
      local_24 = (uint)local_3e + local_2c + -1;
      local_28 = (((*(int *)(param_4 + 0xc) - *(int *)(param_4 + 0x10)) + param_3[1]) - uVar3) -
                 (int)local_38;
      local_20 = uVar3 + local_28 + -1;
      iVar2 = FUN_0003dc3a(&local_2c,*(undefined4 *)(param_1 + 8),0);
      if ((iVar2 == 0) ||
         (iVar2 = FUN_0003dc3a(param_2[3],*(undefined4 *)(param_1 + 8),0), iVar2 == 0)) {
        if (local_44 == 0) {
          *(undefined1 *)(param_2 + 1) = 0;
        }
        else {
          if (local_36 - 1 < 8) {
            iVar2 = FUN_0004173e(param_2[6],0,local_3e,local_3c,0);
            if (iVar2 == 0) {
              if (param_2[6] != 0) {
                FUN_000413fe();
              }
              uVar3 = (uint)local_3c;
              if (local_3e * uVar3 < 0x40) {
                uVar3 = uVar3 << 1;
              }
              iVar2 = FUN_0004137c(&DAT_2003a500,(uint)local_3e,uVar3,0xe,0);
              if (iVar2 == 0) {
                do {
                    /* WARNING: Do nothing block with infinite loop */
                } while( true );
              }
              *(ushort *)(iVar2 + 6) = local_3c;
              param_2[6] = iVar2;
            }
          }
          iVar2 = FUN_00046a2c(&local_44);
          *param_2 = iVar2;
          bVar1 = 0;
          if (iVar2 != 0) {
            bVar1 = local_36;
          }
          *(byte *)(param_2 + 1) = bVar1;
        }
        param_2[2] = (int)&local_2c;
        param_2[4] = (int)&local_44;
        (*param_6)(param_1,param_2,0);
        FUN_00046bda(&local_44);
      }
    }
  }
  return;
}

