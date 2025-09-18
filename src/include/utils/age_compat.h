/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef AG_AGE_COMPAT_H
#define AG_AGE_COMPAT_H

#include "postgres.h"

/*
 * Compatibility macros for supporting both PostgreSQL and Apache Cloudberry
 *
 * This header provides a unified interface for handling differences between
 * PostgreSQL and Apache Cloudberry, allowing AGE to compile and work correctly
 * on both platforms without code duplication.
 */

/* 
 * Check if we're compiling for Apache Cloudberry or standard PostgreSQL
 * GP_VERSION_NUM is defined in Apache Cloudberry but not in standard PostgreSQL
 */
#if defined(GP_VERSION_NUM)
#define AG_CLOUDBERRY 1
#else
#define AG_CLOUDBERRY 0
#endif

/*
 * Type compatibility macros
 *
 * These macros help handle type differences between PostgreSQL and Apache Cloudberry
 */

/* 
 * Integer type handling - both PostgreSQL and Apache Cloudberry use Value for integers
 * This is consistent across both platforms
 */
#define AG_VALUE_INTEGER_TYPE Value
#define AG_MAKE_INTEGER_VALUE makeInteger
#define AG_GET_INTEGER_VALUE(int_val) intVal(int_val)

/*
 * StringInfo type handling - both platforms use the same StringInfo type
 * but we ensure the proper header is included
 */
#include "lib/stringinfo.h"
#define AG_STRINGINFO_TYPE StringInfo

/*
 * Function compatibility macros
 *
 * These macros help handle function signature differences between PostgreSQL and Apache Cloudberry
 */

/* 
 * add_path function handling - Apache Cloudberry requires an additional PlannerInfo *root parameter
 */
#if AG_CLOUDBERRY
#define AG_ADD_PATH(parent_rel, new_path, root) add_path(parent_rel, new_path, root)
#else
#define AG_ADD_PATH(parent_rel, new_path, root) add_path(parent_rel, new_path)
#endif

#endif /* AG_AGE_COMPAT_H */