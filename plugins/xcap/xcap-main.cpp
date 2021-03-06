/* Ekiga -- A VoIP and Video-Conferencing application
 * Copyright (C) 2000-2009 Damien Sandras <dsandras@seconix.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * Ekiga is licensed under the GPL license and as a special exception,
 * you have permission to link or otherwise combine this program with the
 * programs OPAL, OpenH323 and PWLIB, and distribute the combination,
 * without applying the requirements of the GNU GPL to the OPAL, OpenH323
 * and PWLIB programs, as long as you do follow the requirements of the
 * GNU GPL for all the rest of the software thus combined.
 */


/*
 *                         xcap-main.cpp  -  description
 *                         ------------------------------------
 *   begin                : Mon 29 September 2008
 *   copyright            : (C) 2008 by Julien Puydt
 *   description          : Code to hook the XCAP code to the engine
 *
 */

#include "xcap-main.h"
#include "xcap-core.h"

struct XCAPSpark: public Ekiga::Spark
{
  XCAPSpark (): result(false)
  {}

  bool try_initialize_more (Ekiga::ServiceCore& core,
			    int* /*argc*/,
			    char** /*argv*/[])
  {
    Ekiga::ServicePtr service = core.get ("xcap-core");

    if ( !service) {

      boost::shared_ptr<XCAP::Core> xcap(new XCAP::Core ());

      core.add (xcap);
      result = true;
    }

    return result;
  }

  Ekiga::Spark::state get_state () const
  { return result?FULL:BLANK; }

  const std::string get_name () const
  { return "XCAP"; }

  bool result;
};


extern "C" void
ekiga_plugin_init (Ekiga::KickStart& kickstart)
{
  boost::shared_ptr<Ekiga::Spark> spark(new XCAPSpark);
  kickstart.add_spark (spark);
}
