/* Address: CODE:8bf3; name: FUN_CODE_8bf3; body bytes: 31 */

void FUN_CODE_8bf3(undefined1 param_1,undefined1 param_2,char param_3,undefined1 param_4)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  puVar2 = &DAT_EXTMEM_0750;
  uVar1 = BANK0_R5;
  FUN_CODE_6221();
  *puVar2 = param_4;
  puVar2 = (undefined1 *)(CONCAT11(param_2,param_3) + 1);
  *puVar2 = uVar1;
  FUN_CODE_6234(param_3 + '\x04');
  *puVar2 = param_1;
                    /* WARNING: Subroutine does not return */
  FUN_CODE_adf3(0x4c0);
}

