/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_UCBHELPER_MACROS_HXX
#define INCLUDED_UCBHELPER_MACROS_HXX

#include <sal/types.h>
#include <cppuhelper/queryinterface.hxx>
#include <cppuhelper/factory.hxx>
#include <cppuhelper/weakref.hxx>
#include <cppuhelper/supportsservice.hxx>
#include <cppuhelper/typeprovider.hxx>

#include <osl/mutex.hxx>
#include <ucbhelper/getcomponentcontext.hxx>



#define CPPU_TYPE( T )      getCppuType( static_cast< T * >( 0 ) )
#define CPPU_TYPE_REF( T )  CPPU_TYPE( com::sun::star::uno::Reference< T > )

// XTypeProvider impl. internals



#define XTYPEPROVIDER_COMMON_IMPL( Class )                                  \
com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL                          \
Class::getImplementationId()                                                \
    throw( com::sun::star::uno::RuntimeException, std::exception )          \
{                                                                           \
      return css::uno::Sequence<sal_Int8>();                                \
}

#define GETTYPES_IMPL_START( Class )                                        \
com::sun::star::uno::Sequence< com::sun::star::uno::Type > SAL_CALL         \
Class::getTypes()                                                           \
    throw( com::sun::star::uno::RuntimeException, std::exception )          \
{                                                                           \
    static cppu::OTypeCollection* pCollection = NULL;                       \
      if ( !pCollection )                                                     \
      {                                                                       \
        osl::Guard< osl::Mutex > aGuard( osl::Mutex::getGlobalMutex() );    \
        if ( !pCollection )                                                 \
        {                                                                   \
            static cppu::OTypeCollection collection(

#define GETTYPES_IMPL_END                                                   \
                );                                                          \
            pCollection = &collection;                                      \
        }                                                                   \
    }                                                                       \
    return (*pCollection).getTypes();                                       \
}



// XTypeProvider impl.



// 2 interfaces supported
#define XTYPEPROVIDER_IMPL_2( Class, I1,I2 )                                \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 )                                                     \
GETTYPES_IMPL_END

// 3 interfaces supported
#define XTYPEPROVIDER_IMPL_3( Class, I1,I2,I3 )                             \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 )                                                     \
GETTYPES_IMPL_END

// 4 interfaces supported
#define XTYPEPROVIDER_IMPL_4( Class, I1,I2,I3,I4 )                          \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 ),                                                    \
    CPPU_TYPE_REF( I4 )                                                     \
GETTYPES_IMPL_END

// 5 interfaces supported
#define XTYPEPROVIDER_IMPL_5( Class, I1,I2,I3,I4,I5 )                       \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 ),                                                    \
    CPPU_TYPE_REF( I4 ),                                                    \
    CPPU_TYPE_REF( I5 )                                                     \
GETTYPES_IMPL_END

// 6 interfaces supported
#define XTYPEPROVIDER_IMPL_6( Class, I1,I2,I3,I4,I5,I6 )                    \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 ),                                                    \
    CPPU_TYPE_REF( I4 ),                                                    \
    CPPU_TYPE_REF( I5 ),                                                    \
    CPPU_TYPE_REF( I6 )                                                     \
GETTYPES_IMPL_END

// 7 interfaces supported
#define XTYPEPROVIDER_IMPL_7( Class, I1,I2,I3,I4,I5,I6,I7 )                 \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 ),                                                    \
    CPPU_TYPE_REF( I4 ),                                                    \
    CPPU_TYPE_REF( I5 ),                                                    \
    CPPU_TYPE_REF( I6 ),                                                    \
    CPPU_TYPE_REF( I7 )                                                     \
GETTYPES_IMPL_END

// 8 interfaces supported
#define XTYPEPROVIDER_IMPL_8( Class, I1,I2,I3,I4,I5,I6,I7,I8 )              \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 ),                                                    \
    CPPU_TYPE_REF( I4 ),                                                    \
    CPPU_TYPE_REF( I5 ),                                                    \
    CPPU_TYPE_REF( I6 ),                                                    \
    CPPU_TYPE_REF( I7 ),                                                    \
    CPPU_TYPE_REF( I8 )                                                     \
GETTYPES_IMPL_END

// 9 interfaces supported
#define XTYPEPROVIDER_IMPL_9( Class, I1,I2,I3,I4,I5,I6,I7,I8,I9 )           \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 ),                                                    \
    CPPU_TYPE_REF( I4 ),                                                    \
    CPPU_TYPE_REF( I5 ),                                                    \
    CPPU_TYPE_REF( I6 ),                                                    \
    CPPU_TYPE_REF( I7 ),                                                    \
    CPPU_TYPE_REF( I8 ),                                                    \
    CPPU_TYPE_REF( I9 )                                                     \
GETTYPES_IMPL_END

// 10 interfaces supported
#define XTYPEPROVIDER_IMPL_10( Class, I1,I2,I3,I4,I5,I6,I7,I8,I9,I10 )      \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 ),                                                    \
    CPPU_TYPE_REF( I4 ),                                                    \
    CPPU_TYPE_REF( I5 ),                                                    \
    CPPU_TYPE_REF( I6 ),                                                    \
    CPPU_TYPE_REF( I7 ),                                                    \
    CPPU_TYPE_REF( I8 ),                                                    \
    CPPU_TYPE_REF( I9 ),                                                    \
    CPPU_TYPE_REF( I10 )                                                    \
GETTYPES_IMPL_END

// 11 interfaces supported
#define XTYPEPROVIDER_IMPL_11( Class, I1,I2,I3,I4,I5,I6,I7,I8,I9,I10,I11 )  \
XTYPEPROVIDER_COMMON_IMPL( Class )                                          \
GETTYPES_IMPL_START( Class )                                                \
    CPPU_TYPE_REF( I1 ),                                                    \
    CPPU_TYPE_REF( I2 ),                                                    \
    CPPU_TYPE_REF( I3 ),                                                    \
    CPPU_TYPE_REF( I4 ),                                                    \
    CPPU_TYPE_REF( I5 ),                                                    \
    CPPU_TYPE_REF( I6 ),                                                    \
    CPPU_TYPE_REF( I7 ),                                                    \
    CPPU_TYPE_REF( I8 ),                                                    \
    CPPU_TYPE_REF( I9 ),                                                    \
    CPPU_TYPE_REF( I10 ),                                                   \
    CPPU_TYPE_REF( I11 )                                                    \
GETTYPES_IMPL_END

// XServiceInfo impl. internals



#define XSERVICEINFO_COMMOM_IMPL( Class, ImplName )                         \
OUString SAL_CALL Class::getImplementationName()                       \
    throw( com::sun::star::uno::RuntimeException, std::exception )          \
{                                                                           \
    return getImplementationName_Static();                                  \
}                                                                           \
                                                                            \
OUString Class::getImplementationName_Static()                         \
{                                                                           \
    return ImplName;                                                        \
}                                                                           \
                                                                            \
sal_Bool SAL_CALL                                                           \
Class::supportsService( const OUString& ServiceName )                  \
    throw( com::sun::star::uno::RuntimeException, std::exception )          \
{                                                                           \
    return cppu::supportsService( this, ServiceName );                      \
}                                                                           \
                                                                            \
com::sun::star::uno::Sequence< OUString > SAL_CALL                     \
Class::getSupportedServiceNames()                                           \
    throw( com::sun::star::uno::RuntimeException, std::exception )          \
{                                                                           \
    return getSupportedServiceNames_Static();                               \
}

#define XSERVICEINFO_CREATE_INSTANCE_IMPL( Class )                          \
static com::sun::star::uno::Reference<                                      \
                                com::sun::star::uno::XInterface > SAL_CALL  \
Class##_CreateInstance( const com::sun::star::uno::Reference<               \
                com::sun::star::lang::XMultiServiceFactory> & rSMgr )       \
    throw( com::sun::star::uno::Exception )                                 \
{                                                                           \
    com::sun::star::lang::XServiceInfo* pX =                                \
                (com::sun::star::lang::XServiceInfo*)new Class( rSMgr );    \
    return com::sun::star::uno::Reference<                                  \
                            com::sun::star::uno::XInterface >::query( pX ); \
}

#define XSERVICEINFO_CREATE_INSTANCE_IMPL_CTX( Class )                          \
static com::sun::star::uno::Reference<                                      \
                                com::sun::star::uno::XInterface > SAL_CALL  \
Class##_CreateInstance( const com::sun::star::uno::Reference<               \
                com::sun::star::lang::XMultiServiceFactory> & rSMgr )       \
    throw( com::sun::star::uno::Exception )                                 \
{                                                                           \
    com::sun::star::lang::XServiceInfo* pX =                                \
                (com::sun::star::lang::XServiceInfo*)new Class( ucbhelper::getComponentContext(rSMgr) );    \
    return com::sun::star::uno::Reference<                                  \
                            com::sun::star::uno::XInterface >::query( pX ); \
}



// XServiceInfo impl.



#define ONE_INSTANCE_SERVICE_FACTORY_IMPL( Class )                          \
com::sun::star::uno::Reference<                                             \
                        com::sun::star::lang::XSingleServiceFactory >       \
Class::createServiceFactory( const com::sun::star::uno::Reference<          \
            com::sun::star::lang::XMultiServiceFactory >& rxServiceMgr )    \
{                                                                           \
    return com::sun::star::uno::Reference<                                  \
        com::sun::star::lang::XSingleServiceFactory >(                      \
            cppu::createOneInstanceFactory(                                 \
                rxServiceMgr,                                               \
                Class::getImplementationName_Static(),                      \
                Class##_CreateInstance,                                     \
                Class::getSupportedServiceNames_Static() ) );               \
}

// Service without service factory.

// Own implementation of getSupportedServiceNames_Static().
#define XSERVICEINFO_NOFACTORY_IMPL_0( Class, ImplName )                    \
XSERVICEINFO_COMMOM_IMPL( Class, ImplName )                                 \
                                                                            \
com::sun::star::uno::Sequence< OUString >                              \
Class::getSupportedServiceNames_Static()

// 1 service name
#define XSERVICEINFO_NOFACTORY_IMPL_1( Class, ImplName, Service1 )          \
XSERVICEINFO_COMMOM_IMPL( Class, ImplName )                                 \
                                                                            \
com::sun::star::uno::Sequence< OUString >                              \
Class::getSupportedServiceNames_Static()                                    \
{                                                                           \
    com::sun::star::uno::Sequence< OUString > aSNS( 1 );               \
    aSNS.getArray()[ 0 ] = Service1;                                        \
    return aSNS;                                                            \
}

// Service with service factory.

// Own implementation of getSupportedServiceNames_Static().
#define XSERVICEINFO_IMPL_0( Class, ImplName )                              \
XSERVICEINFO_COMMOM_IMPL( Class, ImplName )                                 \
XSERVICEINFO_CREATE_INSTANCE_IMPL( Class )                                  \
                                                                            \
com::sun::star::uno::Sequence< OUString >                              \
Class::getSupportedServiceNames_Static()

// Own implementation of getSupportedServiceNames_Static().
#define XSERVICEINFO_IMPL_0_CTX( Class, ImplName )                              \
XSERVICEINFO_COMMOM_IMPL( Class, ImplName )                                 \
XSERVICEINFO_CREATE_INSTANCE_IMPL_CTX( Class )                                  \
                                                                            \
com::sun::star::uno::Sequence< OUString >                              \
Class::getSupportedServiceNames_Static()

// 1 service name
#define XSERVICEINFO_IMPL_1( Class, ImplName, Service1 )                    \
XSERVICEINFO_COMMOM_IMPL( Class, ImplName )                                 \
XSERVICEINFO_CREATE_INSTANCE_IMPL( Class )                                  \
                                                                            \
com::sun::star::uno::Sequence< OUString >                              \
Class::getSupportedServiceNames_Static()                                    \
{                                                                           \
    com::sun::star::uno::Sequence< OUString > aSNS( 1 );               \
    aSNS.getArray()[ 0 ] = Service1;                                        \
    return aSNS;                                                            \
}

// 1 service name
#define XSERVICEINFO_IMPL_1_CTX( Class, ImplName, Service1 )                    \
XSERVICEINFO_COMMOM_IMPL( Class, ImplName )                                 \
XSERVICEINFO_CREATE_INSTANCE_IMPL_CTX( Class )                                  \
                                                                            \
com::sun::star::uno::Sequence< OUString >                              \
Class::getSupportedServiceNames_Static()                                    \
{                                                                           \
    com::sun::star::uno::Sequence< OUString > aSNS( 1 );               \
    aSNS.getArray()[ 0 ] = Service1;                                        \
    return aSNS;                                                            \
}

#endif /* ! INCLUDED_UCBHELPER_MACROS_HXX */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
