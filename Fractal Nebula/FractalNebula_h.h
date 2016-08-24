

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Aug 13 10:47:38 2016
 */
/* Compiler settings for FractalNebula.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __FractalNebula_h_h__
#define __FractalNebula_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IFractalNebula_FWD_DEFINED__
#define __IFractalNebula_FWD_DEFINED__
typedef interface IFractalNebula IFractalNebula;

#endif 	/* __IFractalNebula_FWD_DEFINED__ */


#ifndef __CFractalNebulaDoc_FWD_DEFINED__
#define __CFractalNebulaDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CFractalNebulaDoc CFractalNebulaDoc;
#else
typedef struct CFractalNebulaDoc CFractalNebulaDoc;
#endif /* __cplusplus */

#endif 	/* __CFractalNebulaDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __FractalNebula_LIBRARY_DEFINED__
#define __FractalNebula_LIBRARY_DEFINED__

/* library FractalNebula */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_FractalNebula;

#ifndef __IFractalNebula_DISPINTERFACE_DEFINED__
#define __IFractalNebula_DISPINTERFACE_DEFINED__

/* dispinterface IFractalNebula */
/* [uuid] */ 


EXTERN_C const IID DIID_IFractalNebula;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5174CC65-0307-431F-B751-4455EEC4ADAA")
    IFractalNebula : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IFractalNebulaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFractalNebula * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFractalNebula * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFractalNebula * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFractalNebula * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFractalNebula * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFractalNebula * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFractalNebula * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IFractalNebulaVtbl;

    interface IFractalNebula
    {
        CONST_VTBL struct IFractalNebulaVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFractalNebula_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFractalNebula_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFractalNebula_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFractalNebula_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFractalNebula_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFractalNebula_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFractalNebula_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IFractalNebula_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CFractalNebulaDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("6857063A-C3D4-4BEE-8ECC-2DBFFAD2EFBA")
CFractalNebulaDoc;
#endif
#endif /* __FractalNebula_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


