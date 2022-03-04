<?php
// Tema suscrito: vehicle_state
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />
    <title>DTC Services Dashboard</title>
    <meta name="description" content="Admin, Dashboard, Bootstrap, Bootstrap 4, Angular, AngularJS" />
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, minimal-ui" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">

    <!-- for ios 7 style, multi-resolution icon of 152x152 -->
    <meta name="apple-mobile-web-app-capable" content="yes">
    <meta name="apple-mobile-web-app-status-barstyle" content="black-translucent">
    <link rel="apple-touch-icon" href="assets/images/logo.png">
    <meta name="apple-mobile-web-app-title" content="Flatkit">
    <!-- for Chrome on Android, multi-resolution icon of 196x196 -->
    <meta name="mobile-web-app-capable" content="yes">
    <link rel="shortcut icon" sizes="196x196" href="assets/images/logo.png">

    <!-- style -->
    <link rel="stylesheet" href="assets/animate.css/animate.min.css" type="text/css" />
    <link rel="stylesheet" href="assets/glyphicons/glyphicons.css" type="text/css" />
    <link rel="stylesheet" href="assets/font-awesome/css/font-awesome.min.css" type="text/css" />
    <link rel="stylesheet" href="assets/material-design-icons/material-design-icons.css" type="text/css" />

    <link rel="stylesheet" href="assets/bootstrap/dist/css/bootstrap.min.css" type="text/css" />
    <!-- build:css assets/styles/app.min.css -->
    <link rel="stylesheet" href="assets/styles/app.css" type="text/css" />
    <!-- endbuild -->
    <link rel="stylesheet" href="assets/styles/font.css" type="text/css" />
</head>

<body>
    <div class="app" id="app">

        <!-- ############ LAYOUT START-->

        <!-- BARRA IZQUIERDA -->
        <!-- aside -->
        <div id="aside" class="app-aside modal nav-dropdown">
            <!-- fluid app aside -->
            <div class="left navside dark dk" data-layout="column">
                <div class="navbar no-radius">
                    <!-- brand -->
                    <a class="navbar-brand">

                        <span class="hidden-folded inline">Capstone</span>
                    </a>
                    <!-- / brand -->
                </div>
                <div class="hide-scroll" data-flex>
                    <nav class="scroll nav-light">
                        <ul class="nav" ui-nav>
                            <li class="nav-header hidden-folded">
                                <small class="text-muted">Main</small>
                            </li>
                            <li>
                                <a href="sdashboard.php">
                                    <span class="nav-icon">
                                        <i class="fa fa-building-o"></i>
                                    </span>
                                    <span class="nav-text">Principal</span>
                                </a>
                            </li>
                            <li>
                                <a href="viajes.php">
                                    <span class="nav-icon">
                                        <i class="fa fa-camera"></i>
                                    </span>
                                    <span class="nav-text">Evidencia de colisión</span>
                                </a>
                            </li>
                            <li>
                                <a href="sagregar.php">
                                    <span class="nav-icon">
                                        <i class="fa fa-bar-chart"></i>
                                    </span>
                                    <span class="nav-text">Velocidad registrada</span>
                                </a>
                            </li>
                            <li>
                                <a href="smodificar.php">
                                    <span class="nav-icon">
                                        <i class="fa fa-map-marker"></i>
                                    </span>
                                    <span class="nav-text">Ubicación del vehículo</span>
                                </a>
                            </li>
                            <li>
                                <a href="empleados.php">
                                    <span class="nav-icon">
                                        <i class="fa fa-lock"></i>
                                    </span>
                                    <span class="nav-text">Cerrar sesión</span>
                                </a>
                            </li>
                        </ul>
                    </nav>
                </div>

            </div>
        </div>
        <!-- / -->

        <!-- content -->
        <div id="content" class="app-content box-shadow-z0" role="main">
            <div class="app-header white box-shadow">
                <div class="navbar navbar-toggleable-sm flex-row align-items-center">
                    <!-- Open side - Naviation on mobile -->
                    <a data-toggle="modal" data-target="#aside" class="hidden-lg-up mr-3">
                        <i class="material-icons">&#xe5d2;</i>
                    </a>
                    <!-- / -->

                    <!-- Page title - Bind to $state's title -->
                    <div class="mb-0 h5 no-wrap" ng-bind="$state.current.data.title" id="pageTitle"></div>

                    <!-- navbar collapse -->
                    <div class="collapse navbar-collapse" id="collapse">
                        <!-- link and dropdown -->
                        <ul class="nav navbar-nav mr-auto">
                            <li class="nav-item dropdown">
                                <a class="nav-link" href data-toggle="dropdown">
                                    <i class="fa fa-fw fa-plus text-muted"></i>
                                    <span>New</span>
                                </a>
                                <div ui-include="'views/blocks/dropdown.new.html'"></div>
                            </li>
                        </ul>

                        <div ui-include="'views/blocks/navbar.form.html'"></div>
                        <!-- / -->
                    </div>
                    <!-- / navbar collapse -->

                    <!-- BARRA DE LA DERECHA -->
                    <ul class="nav navbar-nav ml-auto flex-row">
                        <li class="nav-item dropdown pos-stc-xs">

                            <div ui-include="'views/blocks/dropdown.notification.html'"></div>
                        </li>
                        <li class="nav-item dropdown">

                            <div ui-include="'views/blocks/dropdown.user.html'"></div>
                        </li>
                        <li class="nav-item hidden-md-up">
                            <a class="nav-link pl-2" data-toggle="collapse" data-target="#collapse">
                                <i class="material-icons">&#xe5d4;</i>
                            </a>
                        </li>
                    </ul>
                    <!-- / navbar right -->
                </div>
            </div>


            <!-- PIE DE PAGINA --
            <div class="app-footer">
                <div class="p-2 text-xs">
                    <div class="pull-right text-muted py-1">
                        &copy; Copyright <strong>DTC</strong> <span class="hidden-xs-down">- Built with Love v1.0</span>
                        <a ui-scroll-to="content"><i class="fa fa-long-arrow-up p-x-sm"></i></a>
                    </div>
                    <div class="nav">
                        <a class="nav-link" href="">About</a>
                    </div>
                </div>
            </div> -->

            <div ui-view class="app-body" id="view">


                <!-- SECCION CENTRAL -->
                <div class="padding">
                    <div class="row">
                        <div class="col-xs-12 col-sm-4">


                            <h1 class="row justify-content-center">Estado del Vehículo</h1>

                        </div>
                    </div>

                    <!-- VALORES EN TIEMPO REAL -->
                    <div class="row">
                        <div class="col-xs-15 col-sm-4">
                            <a href="viajes.php">
                                <div class="box p-a">
                                    <div class="pull-left m-r">
                                        <span class="w-48 rounded  primary">
                                            <i data-original="fa fa-2x fa-car" class="fa fa-2x fa-car"></i>
                                        </span>
                                    </div>
                                    <div class="clear">
                                        <h4 class="m-0 text-lg _300"><b id="prin_display">Todo marcha bien </b></h4>
                                        <small class="text-muted"><b id="sec_display">No se han registrado colisiones en el vehículo </b></small>
                                    </div>
                                </div>
                            </a>
                        </div>
                    </div>

                    <!-- Aqui va la tabla -->
                    <div class="row">
                        <!-- SWItCH1 -->

                        <div class="col-sm-6 col-md-4">
                            <div class="box">
                                <div class="box-header">
                                    <h3>Velocidad del vehículo</h3>
                                    <small>Calculados en los ultimos 30 días</small>
                                </div>
                                <div class="box-tool">
                                    <ul class="nav">
                                        <li class="nav-item inline">
                                            <a class="nav-link">
                                                <i class="material-icons md-18">&#xe863;</i>
                                            </a>
                                        </li>
                                        <li class="nav-item inline dropdown">
                                            <a class="nav-link" data-toggle="dropdown">
                                                <i class="material-icons md-18">&#xe5d4;</i>
                                            </a>
                                            <div class="dropdown-menu dropdown-menu-scale pull-right">
                                                <a class="dropdown-item" href>This week</a>
                                                <a class="dropdown-item" href>This month</a>
                                                <a class="dropdown-item" href>This week</a>
                                                <div class="dropdown-divider"></div>
                                                <a class="dropdown-item">Today</a>
                                            </div>
                                        </li>
                                    </ul>
                                </div>
                                <div class="box-body">
                                    <div class="text-center m-b">
                                        <div class="btn-group" data-toggle="buttons">
                                            <label class="btn btn-sm white">
                                                <input type="radio" name="options" autocomplete="off"> Month
                                            </label>
                                            <label class="btn btn-sm white">
                                                <input type="radio" name="options" autocomplete="off"> Day
                                            </label>
                                        </div>
                                    </div>
                                    <div ui-jp="plot" ui-refresh="app.setting.color" ui-options="
                                        [
                                            { data: [[1, 60.6], [2, 60.5], [3, 120], [4, 80], [5, 80.3], [6, 60.5], [7, 60.6]], 
                                            points: { show: true, radius: 0}, 
                                            splines: { show: true, tension: 0.45, lineWidth: 2, fill: 1 }
                                            },
                                            
                                        ], 
                                        {
                                            colors: ['#0cc2aa'],
                                            series: { shadowSize: 3 },
                                            xaxis: { show: true, font: { color: '#ccc' }, position: 'bottom' },
                                            yaxis:{ show: true, font: { color: '#ccc' }},
                                            grid: { hoverable: true, clickable: true, borderWidth: 0, color: 'rgba(120,120,120,0.5)' },
                                            tooltip: true,
                                            tooltipOpts: { content: '%x.0 is %y.4',  defaultTheme: false, shifts: { x: 0, y: -40 } }
                                        }
	                                     " style="height:188px">
                                    </div>
                                </div>
                            </div>
                        </div>

                    </div>


                </div>

                <!-- ############ PAGE END-->

            </div>

        </div>
        <!-- / -->

        <!-- SELECTOR DE TEMAS -->
        <div id="switcher">
            <div class="switcher box-color dark-white text-color" id="sw-theme">
                <a href ui-toggle-class="active" target="#sw-theme" class="box-color dark-white text-color sw-btn">
                    <i class="fa fa-gear"></i>
                </a>
                <div class="box-header">
                    <a href="https://themeforest.net/item/flatkit-app-ui-kit/13231484?ref=flatfull" class="btn btn-xs rounded danger pull-right">BUY</a>
                    <h2>Theme Switcher</h2>
                </div>
                <div class="box-divider"></div>
                <div class="box-body">
                    <p class="hidden-md-down">
                        <label class="md-check m-y-xs" data-target="folded">
                            <input type="checkbox">
                            <i class="green"></i>
                            <span class="hidden-folded">Folded Aside</span>
                        </label>
                        <label class="md-check m-y-xs" data-target="boxed">
                            <input type="checkbox">
                            <i class="green"></i>
                            <span class="hidden-folded">Boxed Layout</span>
                        </label>
                        <label class="m-y-xs pointer" ui-fullscreen>
                            <span class="fa fa-expand fa-fw m-r-xs"></span>
                            <span>Fullscreen Mode</span>
                        </label>
                    </p>
                    <p>Colors:</p>
                    <p data-target="themeID">
                        <label class="radio radio-inline m-0 ui-check ui-check-color ui-check-md" data-value="{primary:'primary', accent:'accent', warn:'warn'}">
                            <input type="radio" name="color" value="1">
                            <i class="primary"></i>
                        </label>
                        <label class="radio radio-inline m-0 ui-check ui-check-color ui-check-md" data-value="{primary:'accent', accent:'cyan', warn:'warn'}">
                            <input type="radio" name="color" value="2">
                            <i class="accent"></i>
                        </label>
                        <label class="radio radio-inline m-0 ui-check ui-check-color ui-check-md" data-value="{primary:'warn', accent:'light-blue', warn:'warning'}">
                            <input type="radio" name="color" value="3">
                            <i class="warn"></i>
                        </label>
                        <label class="radio radio-inline m-0 ui-check ui-check-color ui-check-md" data-value="{primary:'success', accent:'teal', warn:'lime'}">
                            <input type="radio" name="color" value="4">
                            <i class="success"></i>
                        </label>
                        <label class="radio radio-inline m-0 ui-check ui-check-color ui-check-md" data-value="{primary:'info', accent:'light-blue', warn:'success'}">
                            <input type="radio" name="color" value="5">
                            <i class="info"></i>
                        </label>
                        <label class="radio radio-inline m-0 ui-check ui-check-color ui-check-md" data-value="{primary:'blue', accent:'indigo', warn:'primary'}">
                            <input type="radio" name="color" value="6">
                            <i class="blue"></i>
                        </label>
                        <label class="radio radio-inline m-0 ui-check ui-check-color ui-check-md" data-value="{primary:'warning', accent:'grey-100', warn:'success'}">
                            <input type="radio" name="color" value="7">
                            <i class="warning"></i>
                        </label>
                        <label class="radio radio-inline m-0 ui-check ui-check-color ui-check-md" data-value="{primary:'danger', accent:'grey-100', warn:'grey-300'}">
                            <input type="radio" name="color" value="8">
                            <i class="danger"></i>
                        </label>
                    </p>
                    <p>Themes:</p>
                    <div data-target="bg" class="row no-gutter text-u-c text-center _600 clearfix">
                        <label class="p-a col-sm-6 light pointer m-0">
                            <input type="radio" name="theme" value="" hidden>
                            Light
                        </label>
                        <label class="p-a col-sm-6 grey pointer m-0">
                            <input type="radio" name="theme" value="grey" hidden>
                            Grey
                        </label>
                        <label class="p-a col-sm-6 dark pointer m-0">
                            <input type="radio" name="theme" value="dark" hidden>
                            Dark
                        </label>
                        <label class="p-a col-sm-6 black pointer m-0">
                            <input type="radio" name="theme" value="black" hidden>
                            Black
                        </label>
                    </div>
                </div>
            </div>
        </div>
        <!-- / -->

        <!-- ############ LAYOUT END-->

    </div>
    <!-- build:js scripts/app.html.js -->
    <!-- jQuery -->
    <script src="libs/jquery/jquery/dist/jquery.js"></script>
    <!-- Bootstrap -->
    <script src="libs/jquery/tether/dist/js/tether.min.js"></script>
    <script src="libs/jquery/bootstrap/dist/js/bootstrap.js"></script>
    <!-- core -->
    <script src="libs/jquery/underscore/underscore-min.js"></script>
    <script src="libs/jquery/jQuery-Storage-API/jquery.storageapi.min.js"></script>
    <script src="libs/jquery/PACE/pace.min.js"></script>

    <script src="html/scripts/config.lazyload.js"></script>

    <script src="html/scripts/palette.js"></script>
    <script src="html/scripts/ui-load.js"></script>
    <script src="html/scripts/ui-jp.js"></script>
    <script src="html/scripts/ui-include.js"></script>
    <script src="html/scripts/ui-device.js"></script>
    <script src="html/scripts/ui-form.js"></script>
    <script src="html/scripts/ui-nav.js"></script>
    <script src="html/scripts/ui-screenfull.js"></script>
    <script src="html/scripts/ui-scroll-to.js"></script>
    <script src="html/scripts/ui-toggle-class.js"></script>

    <script src="html/scripts/app.js"></script>

    <!-- ajax -->
    <script src="libs/jquery/jquery-pjax/jquery.pjax.js"></script>
    <script src="html/scripts/ajax.js"></script>

    <script src="https://unpkg.com/mqtt/dist/mqtt.min.js"></script>
    <script type="text/javascript">
        /*
         ******************************
         ****** PROCESOS  *************
         ******************************
         */


        function update_values() {
            console.log("Aqui si llega");
            $("#prin_display").html("¡Incidente detectado!");
            $("#sec_display").html("Evidencia disponible");
            console.log("cambio de nombre ejecutado");
            var i = $(this).find('i');
            i.attr('class', i.hasClass('fa-plus-circle') ? 'fa fa-minus' : i.attr('data-original'));
        }

        function process_msg(topic, message) {
            // ej: "Crushed!"
            if (topic == "vehicle_state") {
                var valor = message.toString(); // message.toString();
                console.log(valor);
                if (valor == "Crushed!") update_values();
            }
        }


        /*
         ******************************
         ****** CONEXION  *************
         ******************************
         */

        // connect options
        const options = {
            connectTimeout: 4000,

            // Authentication
            clientId: 'iotmc',
            username: 'web_client',
            password: '121212',

            keepalive: 60,
            clean: true,
        }

        var connected = false;

        // WebSocket connect url
        const WebSocket_URL = 'wss://realdtc.ga:8094/mqtt'


        const client = mqtt.connect(WebSocket_URL, options)


        client.on('connect', () => {
            console.log('Mqtt conectado por WS! Exito!')

            client.subscribe('vehicle_state', {
                qos: 0
            }, (error) => {
                if (!error) {
                    console.log('Suscripción exitosa!')
                } else {
                    console.log('Suscripción fallida!')
                }
            })
        })

        client.on('message', (topic, message) => {
            console.log('Mensaje recibido bajo tópico: ', topic, ' -> ', message.toString())
            process_msg(topic, message);
        })

        client.on('reconnect', (error) => {
            console.log('Error al reconectar', error)
        })

        client.on('error', (error) => {
            console.log('Error de conexión:', error)
        })
    </script>



    <!-- endbuild -->
</body>

</html>