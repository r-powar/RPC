/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "airports.h"

bool_t
xdr_stringtype (XDR *xdrs, stringtype *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, 255))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airportlist (XDR *xdrs, airportlist *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)objp, sizeof (struct airportnode), (xdrproc_t) xdr_airportnode))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airportnode (XDR *xdrs, airportnode *objp)
{
	register int32_t *buf;

	 if (!xdr_stringtype (xdrs, &objp->code))
		 return FALSE;
	 if (!xdr_stringtype (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->latitude))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->longitude))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->distance))
		 return FALSE;
	 if (!xdr_airportlist (xdrs, &objp->next))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airportdata (XDR *xdrs, airportdata *objp)
{
	register int32_t *buf;

	 if (!xdr_float (xdrs, &objp->latitude))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->longitude))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airport_ret (XDR *xdrs, airport_ret *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->err))
		 return FALSE;
	switch (objp->err) {
	case 0:
		 if (!xdr_airportlist (xdrs, &objp->airport_ret_u.list))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}
