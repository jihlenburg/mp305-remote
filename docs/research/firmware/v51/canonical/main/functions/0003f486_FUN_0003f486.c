/* Address: 0003f486; name: FUN_0003f486; body bytes: 56 */

undefined8 FUN_0003f486(int param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  undefined2 local_1c;
  undefined1 local_1a;
  
  iVar1 = FUN_0004a162(param_1 + 0x38);
  if (iVar1 != 0) {
    FUN_0004f266(iVar1,0x7fffffff);
    *(undefined4 *)(iVar1 + 8) = 0x7fffffff;
    *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xfffffeff;
    local_1c = (undefined2)param_2;
    *(undefined2 *)(iVar1 + 0xc) = local_1c;
    local_1a = (undefined1)((uint)param_2 >> 0x10);
    *(undefined1 *)(iVar1 + 0xe) = local_1a;
    *(undefined1 *)(iVar1 + 0x14) = param_3;
    return CONCAT44(param_1,iVar1);
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}

