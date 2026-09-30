/* Address: 0004f314; name: FUN_0004f314; body bytes: 86 */

void FUN_0004f314(void)

{
  FUN_00063334();
  DAT_1ffe013c = FUN_00047ef8();
  FUN_00048898(DAT_1ffe013c,1);
  FUN_00048890(DAT_1ffe013c,0x632dd);
  DAT_1ffe0140 = (char *)FUN_00047ef8();
  FUN_00048898(DAT_1ffe0140,2);
  FUN_00048890(DAT_1ffe0140,0x3b05d);
  DAT_1ffe0144 = FUN_000471a4();
  if ((DAT_1ffe0140 != (char *)0x0) && ((*DAT_1ffe0140 == '\x02' || (*DAT_1ffe0140 == '\x04')))) {
    *(undefined4 *)(DAT_1ffe0140 + 0xa8) = DAT_1ffe0144;
  }
  return;
}

