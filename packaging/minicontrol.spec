Name:       minicontrol
Summary:    minicontrol library
Version:    0.0.16
Release:    1
VCS:        magnolia/apps/home/minicontrol#minicontrol_0.0.5-3-12-g9f2120dd83e9a1f726a621f2ac36bb6ddcce6e95
Group:      TBD
License:    TBD
Source0:    %{name}-%{version}.tar.gz
BuildRequires: pkgconfig(dbus-1)
BuildRequires: pkgconfig(dbus-glib-1)
BuildRequires: pkgconfig(elementary)
BuildRequires: pkgconfig(evas)
BuildRequires: pkgconfig(ecore-evas)
BuildRequires: pkgconfig(dlog)
BuildRequires: cmake
Requires(post): /sbin/ldconfig
requires(postun): /sbin/ldconfig
%description
Minicontrol library.

%prep
%setup -q

%package devel
Summary:    Minicontrol library (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
Minicontrol library (devel).

%build
%if 0%{?tizen_build_binary_release_type_eng}
export CFLAGS="$CFLAGS -DTIZEN_ENGINEER_MODE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_ENGINEER_MODE"
export FFLAGS="$FFLAGS -DTIZEN_ENGINEER_MODE"
%endif
%if 0%{?sec_build_binary_debug_enable}
export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"
%endif
export LDFLAGS+="-Wl,--rpath=%{_prefix}/lib -Wl,--as-needed"
LDFLAGS="$LDFLAGS" cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}
make %{?jobs:-j%jobs}

%install
%make_install

mkdir -p %{buildroot}/usr/share/license
cp -f LICENSE %{buildroot}/usr/share/license/%{name}


%post
/sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest minicontrol.manifest
%defattr(-,root,root,-)
%{_libdir}/libminicontrol-provider.so*
%{_libdir}/libminicontrol-viewer.so*
%{_libdir}/libminicontrol-monitor.so*
/usr/share/license/%{name}

%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}/*.h
%{_libdir}/pkgconfig/minicontrol-provider.pc
%{_libdir}/pkgconfig/minicontrol-monitor.pc
%{_libdir}/pkgconfig/minicontrol-viewer.pc

