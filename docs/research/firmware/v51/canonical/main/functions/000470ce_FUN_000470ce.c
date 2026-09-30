/* Address: 000470ce; name: FUN_000470ce; body bytes: 118 */

int * FUN_000470ce(int param_1,int param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  
  if ((*(byte *)(param_1 + 0xb) & 7) == 0) {
    return (int *)0x0;
  }
  switch(*(byte *)(param_1 + 0xb) & 7) {
  case 1:
    break;
  case 2:
  case 3:
  case 4:
  case 5:
    param_3 = param_2;
    break;
  default:
    param_3 = 0x40;
  }
  uVar2 = param_3 * 3 + 3U & 0xfffffffc;
  piVar1 = (int *)FUN_0004a318((param_3 + 3U & 0xfffffffc) + uVar2 + 0xc);
  if (piVar1 == (int *)0x0) {
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  *piVar1 = (int)(piVar1 + 3);
  piVar1[1] = (int)piVar1 + uVar2 + 0xc;
  piVar1[2] = param_3;
  for (uVar2 = 0; uVar2 < (uint)piVar1[2]; uVar2 = uVar2 + 1) {
    FUN_00046faa(param_1,piVar1[2],uVar2,*piVar1 + uVar2 * 3,piVar1[1] + uVar2);
  }
  return piVar1;
}

